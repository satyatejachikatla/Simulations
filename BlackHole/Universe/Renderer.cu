#include <Universe/Renderer.cuh>

__global__ void Render(DeviceCamera **d_camera_ptr,vec3 *d_fb,UniformsList l) {

	DeviceCamera* d_camera = *d_camera_ptr;

	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;

	if((i >= d_camera -> d_width) || (j >= d_camera -> d_height)) return;

	int pixel_index = j*(d_camera -> d_width) + i;

	float s,c;
	float t = *l.u_time *1;
	sincos(t,&s,&c);

	d_fb[pixel_index] = vec3(s,1-s,1.0f);
}


