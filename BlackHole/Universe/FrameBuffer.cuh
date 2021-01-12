#ifndef SIMULATION_BLACKHOLE_UNIVERSE_FRAMEBUFFER_
#define SIMULATION_BLACKHOLE_UNIVERSE_FRAMEBUFFER_

#include <vector>
#include <CudaVector.cuh>

struct FrameBuffer {

	int size;
	vec3* d_frame_buffer;
	std::vector<vec3> h_frame_buffer;

	FrameBuffer(int size);
	~FrameBuffer();

	void copyDeviceToHost();

};

#endif /* SIMULATION_BLACKHOLE_UNIVERSE_FRAMEBUFFER_ */