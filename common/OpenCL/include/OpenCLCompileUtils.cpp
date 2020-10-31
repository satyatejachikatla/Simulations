#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY

#include <CL/cl2.hpp>
#include <string>
#include <fstream>
#include <iostream>

#include <OpenCLCompileUtils.hpp>

#if CL_HPP_TARGET_OPENCL_VERSION == 110
	#define COMPILE_OPTION "-cl-std=CL1.1"
#elif CL_HPP_TARGET_OPENCL_VERSION == 120
	#define COMPILE_OPTION "-cl-std=CL1.2"
#elif  CL_HPP_TARGET_OPENCL_VERSION == 200
	#define COMPILE_OPTION "-cl-std=CL2.1"
#else
	#error "Bad CL config option CL_HPP_TARGET_OPENCL_VERSION"
#endif

using namespace std;

cl::Program OpenCLCreateProgram(const std::string& file) {

	std::cout << "Compiling kernel : " << file << std::endl;
	std::cout << "Will be selecting first available platform and device"<< std::endl;

	std::vector<cl::Platform> platforms;
	checkOpenCLErrors(cl::Platform::get(&platforms));
	auto platform = platforms.front();

	std::vector<cl::Device> devices;
	checkOpenCLErrors(platform.getDevices(CL_DEVICE_TYPE_GPU,&devices));
	auto device = devices.front();
	auto name    = device.getInfo<CL_DEVICE_NAME>();
	auto vendor  = device.getInfo<CL_DEVICE_VENDOR>();
	auto version = device.getInfo<CL_DRIVER_VERSION>();

	std::cout << "Device Name    :"<< name    << std::endl;
	std::cout << "Device Vendor  :"<< vendor  << std::endl;
	std::cout << "Device Version :"<< version << std::endl;

	std::ifstream programFile(file);
	std::string src((std::istreambuf_iterator<char>(programFile)),
					 std::istreambuf_iterator<char>());

	// std::cout << "Source : " << std::endl;
	// std::cout << src << std::endl;

	cl::Program::Sources sources(1,std::make_pair(src.c_str() , src.length() + 1));

	cl::Context context(device);
	cl::Program program(context,sources);

	int status = program.build(COMPILE_OPTION);

	std::cout << "Build Info :" << std::endl;
	std::cout << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << "\n";
	std::cout << "-------------------------------------------------" << std::endl;
	if(status != CL_SUCCESS)
	{

		exit(EXIT_FAILURE);
	}

	return program;
}