#ifndef SIMULATION_FLOCKING_BOIDS_BOID_
#define SIMULATION_FLOCKING_BOIDS_BOID_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class Boid {

private:

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;

	float limit_velocity_mag;
	float limit_acceleration_mag;

	float cohesion_steering_mag;
	float aling_steering_mag;

	void Limit(glm::vec2& quantity,float limit_mag);
	void SetMag(glm::vec2& quantity,float mag);

public:
	Boid() = delete;
	explicit Boid(glm::vec2 position,glm::vec2 velocity,glm::vec2 acceleration);

	void Align(const std::vector<Boid*>& neighbours);
	void Cohesion(const std::vector<Boid*>& neighbours);
	void Update();
	void UpdatePositionToBounds(const glm::vec2& bounds);

	void ClearAcceleration() { acceleration*=0.0f; }
	const glm::vec2& GetPosition() { return position; }
	const glm::vec2& GetVelocity() { return velocity; }
	const glm::vec2& GetAcceleration() { return acceleration; }

};

#endif /*SIMULATION_FLOCKING_BOIDS_BOID_*/