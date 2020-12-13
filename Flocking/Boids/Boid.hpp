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
	float limit_aling_steering_mag;

	void ApplyLimits();

public:
	Boid() = delete;
	explicit Boid(glm::vec2 position,glm::vec2 velocity,glm::vec2 acceleration);

	void Align(const float preception_radius, const std::vector<Boid>& neighbours);
	void Update();
	void UpdatePositionToBounds(const glm::vec2& bounds);

	const glm::vec2& GetPosition() { return position; }
	const glm::vec2& GetVelocity() { return velocity; }
	const glm::vec2& GetAcceleration() { return acceleration; }

};

#endif /*SIMULATION_FLOCKING_BOIDS_BOID_*/