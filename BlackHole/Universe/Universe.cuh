#ifndef SIMULATION_BLACKHOLE_UNIVERSE_UNIVERSE_
#define SIMULATION_BLACKHOLE_UNIVERSE_UNIVERSE_


#include <vector>

#include <Universe/Bodies/Body.cuh>
#include <Universe/Camera.cuh>

struct UniverseConfig {

	int width;
	int height;

};

class Universe {

private:

	Camera h_camera;

public:


	void step();
	const std::vector<vec3>& getImage() { return h_camera.getImage(); }

	Universe(UniverseConfig& c);
	~Universe();
};

#endif /*SIMULATION_BLACKHOLE_UNIVERSE_UNIVERSE_*/