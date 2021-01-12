#include <Universe/Camera.cuh>
#include <iostream>

using namespace std;

__global__ void Render(DeviceCamera **d_camera_ptr,vec3 *d_fb) {

	DeviceCamera* d_camera = *d_camera_ptr;

	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;

	if((i >= d_camera -> d_width) || (j >= d_camera -> d_height)) return;

	int pixel_index = j*(d_camera -> d_width) + i;

	d_fb[pixel_index] = vec3((float)i/(d_camera -> d_width),(float)j / (d_camera -> d_height),1.0f);
}


__global__ void CameraInit(
	int width,
	int height,
	DeviceCamera **d_camera_ptr) {
		if (threadIdx.x == 0 && blockIdx.x == 0) {
			//printf("CameraInitBegin\n");
			*d_camera_ptr = new DeviceCamera(width,height);
		}
}
__global__ void CameraCleanup(
	DeviceCamera **d_camera_ptr) {
		if (threadIdx.x == 0 && blockIdx.x == 0) {
			delete *d_camera_ptr;
		}
}

__device__ DeviceCamera::DeviceCamera(int width,int height){
	d_width = width;
	d_height = height;
}
__device__ DeviceCamera::~DeviceCamera(){
}
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

Camera::Camera(int width,int height) :
	fb(width*height){

	/* Max threads per block in my pc, divided equaly across the width and height */
	const unsigned int tx = 32;
	const unsigned int ty = 32;
	
	blocks = dim3(width/tx+1,height/ty+1);
	threads = dim3(tx,ty);

	h_width = width;
	h_height = height;

	checkCudaErrors(cudaMalloc((void **)&d_camera, sizeof(DeviceCamera *)));

	CameraInit<<<1,1>>>(
		h_width,
		h_height,
		d_camera);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());
}

Camera::~Camera() {
	CameraCleanup<<<1,1>>>(
		d_camera);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	checkCudaErrors(cudaFree(d_camera));
}

const std::vector<vec3>& Camera::getImage(){
	
	Render<<<blocks,threads>>>(d_camera,fb.d_frame_buffer);
	fb.copyDeviceToHost();

	return fb.h_frame_buffer;
}