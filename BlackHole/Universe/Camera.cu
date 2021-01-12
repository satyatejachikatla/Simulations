#include <Universe/Camera.cuh>
#include <Universe/FrameBuffer.cuh>
#include <Universe/Renderer.cuh>

#include <iostream>

using namespace std;

__global__ void CameraInit(
	int width,
	int height,
	DeviceCamera **d_camera_ptr) {
		if (threadIdx.x == 0 && blockIdx.x == 0) {
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

const std::vector<vec3>& Camera::getImage(UniformsList l){
	
	Render<<<blocks,threads>>>(d_camera,fb.d_frame_buffer,l);
	fb.copyDeviceToHost();

	return fb.h_frame_buffer;
}