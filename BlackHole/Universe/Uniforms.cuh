#ifndef SIMULATION_BLACKHOLE_UNIVERSE_UNIFORMS_
#define SIMULATION_BLACKHOLE_UNIVERSE_UNIFORMS_

#include <CudaErrors.cuh>
#include <CudaVector.cuh>

struct UniformsList {
	long* u_time;
	vec2* u_resolution;
};

template<typename T>
class Uniform {
private :
	T* d_data;
public:

	Uniform() {
		checkCudaErrors(cudaMallocManaged((void**)&d_data, sizeof(T)));
	}
	T* getAddress() { return d_data; }
	T getData() { return *d_data; }
	void setData(T d) { *d_data = d; }

	~Uniform() {
		checkCudaErrors(cudaFree(d_data));	
	}
};

#endif /* SIMULATION_BLACKHOLE_UNIVERSE_UNIFORMS_ */