#include <Universe/Camera.cuh>
#include <iostream>

using namespace std;

__global__ void render(DeviceCamera **d_camera_ptr,FrameBuffer **d_fb_ptr) {

	DeviceCamera* d_camera = *d_camera_ptr;
	FrameBuffer* d_fb = *d_fb_ptr;

	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;

	if((i >= d_camera -> d_width) || (j >= d_camera -> d_height)) return;

	int pixel_index = j*(d_camera -> d_width) + i;
}


__global__ void CameraInit(
	int width,
	int height,
	DeviceCamera **d_camera_ptr,
	FrameBuffer **d_fb_ptr) {
		if (threadIdx.x == 0 && blockIdx.x == 0) {
			//printf("CameraInitBegin\n");
			*d_camera_ptr = new DeviceCamera(width,height);
			*d_fb_ptr = new FrameBuffer(width*height);

		}
}
__global__ void CameraCleanup(
	DeviceCamera **d_camera_ptr,
	FrameBuffer **d_fb_ptr) {
		if (threadIdx.x == 0 && blockIdx.x == 0) {
			delete *d_camera_ptr;
			delete *d_fb_ptr;
		}
}

__device__ DeviceCamera::DeviceCamera(int width,int height){
	d_width = width;
	d_height = height;
}
__device__ DeviceCamera::~DeviceCamera(){
}
__device__ FrameBuffer::FrameBuffer(int s){
	size = s;
	d_frame_buffer = new vec3[size];
}
__device__ FrameBuffer::~FrameBuffer(){
	delete d_frame_buffer;
}

Camera::Camera(int width,int height) {
	h_width = width;
	h_height = height;

	h_image.resize(width*height,vec3(0.0f,0.0f,0.0f)); 

	checkCudaErrors(cudaMalloc((void **)&d_camera, sizeof(DeviceCamera *)));
	checkCudaErrors(cudaMalloc((void **)&d_fb, sizeof(FrameBuffer *)));

	CameraInit<<<1,1>>>(
		h_width,
		h_height,
		d_camera,
		d_fb);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());
}

Camera::~Camera() {
	CameraCleanup<<<1,1>>>(
		d_camera,
		d_fb);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	checkCudaErrors(cudaFree(d_camera));
	checkCudaErrors(cudaFree(d_fb));
}

const std::vector<vec3>& Camera::getImage(){

	render<<<1,1>>>(d_camera,d_fb);

	return h_image;
}