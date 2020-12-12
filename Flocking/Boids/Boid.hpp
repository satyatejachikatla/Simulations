#ifndef SIMULATION_FLOCKING_BOIDS_BOID_
#define SIMULATION_FLOCKING_BOIDS_BOID_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class Boid {

private:

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;

public:
	Boid() = delete;
	explicit Boid(glm::vec2 position,glm::vec2 velocity,glm::vec2 acceleration);

	void Update();

};

#endif /*SIMULATION_FLOCKING_BOIDS_BOID_*/