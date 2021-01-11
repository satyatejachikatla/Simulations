#ifndef SIMULATION_BLACKHOLE_UNIVERSE_CAMERA_
#define SIMULATION_BLACKHOLE_UNIVERSE_CAMERA_


#include <vector>

#include <CudaErrors.cuh>
#include <CudaVector.cuh>
#include <Universe/Bodies/Body.cuh>


struct FrameBuffer {

	int size;
	vec3* d_frame_buffer;

	__device__ FrameBuffer(int size);
	__device__ ~FrameBuffer();
};

struct DeviceCamera {

	int d_width;
	int d_height;
	__device__ DeviceCamera(int d_width,int d_height);
	__device__ ~DeviceCamera();

};


class Camera {

private:

	int h_width;
	int h_height;
	std::vector<vec3> h_image;

	DeviceCamera** d_camera;
	FrameBuffer** d_fb;

public:

	Camera(int width,int height);
	~Camera();

	int getWidth() { return h_width; }
	int getHeight() { return h_height; }

	const std::vector<vec3>& getImage();

};

#endif /*SIMULATION_BLACKHOLE_UNIVERSE_CAMERA_*/