#ifndef SIMULATION_BLACKHOLE_UNIVERSE_UNIVERSE_
#define SIMULATION_BLACKHOLE_UNIVERSE_UNIVERSE_


#include <vector>

#include <Universe/Bodies/Body.cuh>
#include <Universe/Camera.cuh>
#include <Universe/Uniforms.cuh>

struct UniverseConfig {

	int width;
	int height;

};

class Universe {

private:

	Camera h_camera;
	long h_start_time;

	Uniform<long> u_time;

	UniformsList l;

public:


	void step();
	const std::vector<vec3>& getImage() { return h_camera.getImage(l); }

	Universe(UniverseConfig& c);
	~Universe();
};

#endif /*SIMULATION_BLACKHOLE_UNIVERSE_UNIVERSE_*/