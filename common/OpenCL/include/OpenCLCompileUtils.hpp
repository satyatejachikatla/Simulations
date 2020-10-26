#ifndef _OPENCL_COMPILE_UTILS_H_
#define _OPENCL_COMPILE_UTILS_H_

#include <CL/cl2.hpp>
#include <OpenCLErrors.hpp>

cl::Program OpenCLCreateProgram(const std::string& file);

#endif /*_OPENCL_COMPILE_UTILS_H_*/
