#ifndef SIMULATION_FLOCKING_BOIDS_FLOCK_
#define SIMULATION_FLOCKING_BOIDS_FLOCK_

#include <vector>

#include <Boids/Boid.hpp>

class Flock {

private:

	glm::vec2 bounds;

	float preception_radius = 5.0f;

	std::vector<Boid> boids;

public:

	Flock() = delete;
	explicit Flock(int number_of_boids,int width,int height);

	void Update();

	const int GetWidth() const { return bounds.x; }
	const int GetHeight() const { return bounds.y; }
	const std::vector<Boid>& GetBoids() { return boids; }

};

#endif /*SIMULATION_FLOCKING_BOIDS_FLOCK_*/