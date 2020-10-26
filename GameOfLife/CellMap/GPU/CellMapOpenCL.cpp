#include <vector>
#include <iostream>
#include <cmath>

#include <CellMap/GPU/CellMapOpenCL.hpp>

using namespace std;

#define MAX_THREADS_IN_AXIS 32.0

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

	cl::NDRange blocks(ceil(width/MAX_THREADS_IN_AXIS),ceil(height/MAX_THREADS_IN_AXIS));
	cl::NDRange threads(MAX_THREADS_IN_AXIS,MAX_THREADS_IN_AXIS);



	cl::CommandQueue queue(context);

	uint8_t* cells_data = cells->data();

	queue.enqueueWriteBuffer(cells_gpu,CL_TRUE,0,sizeof(bool)*width*height,cells_data);

	for(int c=0;c<step_count;c++) {
		if (c%2 == 0) {
			kernel.setArg(0,cells_gpu);
			kernel.setArg(1,cells_gpu_temp);
		} else {
			kernel.setArg(1,cells_gpu);
			kernel.setArg(0,cells_gpu_temp);			
		}
		kernel.setArg(2,width);
		kernel.setArg(3,height);
		kernel.setArg(4,edgeWrap);
		queue.enqueueNDRangeKernel(kernel,cl::NullRange,blocks,threads);
	}
	if(step_count%2==0) {
		queue.enqueueReadBuffer(cells_gpu,CL_TRUE,0,sizeof(bool)*width*height,cells_data);
	} else {
		queue.enqueueReadBuffer(cells_gpu_temp,CL_TRUE,0,sizeof(bool)*width*height,cells_data);
	}

}