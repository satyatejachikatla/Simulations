#include <Universe/FrameBuffer.cuh>
#include <CudaErrors.cuh>

FrameBuffer::FrameBuffer(int s){
	size = s;
	checkCudaErrors(cudaMalloc((void **)&d_frame_buffer, sizeof(vec3)*size));

	h_frame_buffer.resize(size,vec3(0.0f,0.0f,0.0f)); 
}

FrameBuffer::~FrameBuffer(){
	checkCudaErrors(cudaFree(d_frame_buffer));
}

void FrameBuffer::copyDeviceToHost(){
	checkCudaErrors(cudaMemcpy(h_frame_buffer.data(),d_frame_buffer,size*sizeof(vec3),cudaMemcpyDeviceToHost));
}
