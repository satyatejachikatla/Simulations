#ifndef SIMULATION_FLOCKING_BOIDS_FLOCK_
#define SIMULATION_FLOCKING_BOIDS_FLOCK_

#include <vector>

#include <Boids/Boid.hpp>

class Flock {

private:

	int width;
	int height;

	std::vector<Boid> boids;

public:

	Flock() = delete;
	explicit Flock(int number_of_boids,int width,int height);

	void Update();

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

};

#endif /*SIMULATION_FLOCKING_BOIDS_FLOCK_*/