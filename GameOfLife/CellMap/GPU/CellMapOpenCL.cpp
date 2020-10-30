#include <vector>
#include <iostream>
#include <cmath>

#include <OpenCLErrors.hpp>
#include <CellMap/GPU/CellMapOpenCL.hpp>

using namespace std;

CellMapOpenCL::CellMapOpenCL(int width, int height, bool edge_wrap) :
	CellMap(width,height,edge_wrap) {

		/* Setup OpenCL env */
		program  = OpenCLCreateProgram(CELLMAP_OPENCL_PROGRAM);
		context  = program.getInfo<CL_PROGRAM_CONTEXT>();
		auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
		device  = devices.front();

		/* Setup GPU Buffers */
		cells_gpu = cl::Buffer(context,CL_MEM_READ_WRITE, sizeof(bool) * width * height);
		cells_gpu_temp = cl::Buffer(context,CL_MEM_READ_WRITE, sizeof(bool) * width * height);

		/* Make Kernel*/
		kernel   = cl::Kernel(program,"CellMapOpenCLStep");

}
CellMapOpenCL::~CellMapOpenCL(){

}


void CellMapOpenCL::Step(int step_count) {


	int MAX_THREADS_IN_AXIS= 1;//sqrt(kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device));
	cl::NDRange blocks(ceil(width/MAX_THREADS_IN_AXIS),ceil(height/MAX_THREADS_IN_AXIS));
	cl::NDRange threads(MAX_THREADS_IN_AXIS,MAX_THREADS_IN_AXIS);

	cl::CommandQueue queue(context);

	checkOpenCLErrors(queue.enqueueWriteBuffer(cells_gpu,CL_TRUE,0,sizeof(bool)*width*height,cells->data()));

	for(int c=0;c<step_count;c++) {
		if (c%2 == 0) {
			checkOpenCLErrors(kernel.setArg(0,cells_gpu));
			checkOpenCLErrors(kernel.setArg(1,cells_gpu_temp));
		} else {
			checkOpenCLErrors(kernel.setArg(1,cells_gpu));
			checkOpenCLErrors(kernel.setArg(0,cells_gpu_temp));			
		}
		checkOpenCLErrors(kernel.setArg(2,width));
		checkOpenCLErrors(kernel.setArg(3,height));
		checkOpenCLErrors(kernel.setArg(4,edgeWrap));
		checkOpenCLErrors(queue.enqueueNDRangeKernel(kernel,cl::NullRange,blocks,threads));
	}
	if(step_count%2==0) {
		checkOpenCLErrors(queue.enqueueReadBuffer(cells_gpu,CL_TRUE,0,sizeof(bool)*width*height,cells->data()));
	} else {
		checkOpenCLErrors(queue.enqueueReadBuffer(cells_gpu_temp,CL_TRUE,0,sizeof(bool)*width*height,cells->data()));
	}

}