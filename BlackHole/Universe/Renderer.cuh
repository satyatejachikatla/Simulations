#ifndef SIMULATION_BLACKHOLE_UNIVERSE_RENDERER_
#define SIMULATION_BLACKHOLE_UNIVERSE_RENDERER_

#include <CudaVector.cuh>
#include <Universe/Camera.cuh>
#include <Universe/FrameBuffer.cuh>
#include <Universe/Uniforms.cuh>

__global__ void Render(DeviceCamera **d_camera_ptr,vec3 *d_fb,UniformsList l);

#endif /* SIMULATION_BLACKHOLE_UNIVERSE_RENDERER_ */