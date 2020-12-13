#include <Boids/Boid.hpp>

#include <iostream>
#include <math.h>

using namespace std;

Boid::Boid(glm::vec2 position,glm::vec2 velocity,glm::vec2 acceleration) :
	limit_velocity_mag(5.0f) , 
	limit_acceleration_mag(5.0f), 
	limit_aling_steering_mag(0.001f),


	position(position),
	velocity(velocity),
	acceleration(acceleration)
	{
}

void Boid::ApplyLimits() {
	if(glm::length(velocity) > limit_velocity_mag) 
		velocity = glm::normalize(velocity)*limit_velocity_mag;
	if(glm::length(acceleration) > limit_acceleration_mag)
		acceleration = glm::normalize(acceleration)*limit_acceleration_mag;
}

void Boid::Align(const float preception_radius, const std::vector<Boid>& neighbours){
	
	int preception_radius_boid_count = 0;

	glm::vec2 preception_radius_direction = glm::vec2(0.0f);
	glm::vec2 steering = glm::vec2(0.0f);

	for ( auto n : neighbours) {
		if ( &n == this ) continue;

		glm::vec2 p1 = n.GetPosition();
		glm::vec2 p2 = this->GetPosition();

		float dist_btwn_boids = glm::distance(p1,p2);

		if(dist_btwn_boids > preception_radius) continue;

		preception_radius_boid_count ++;
		preception_radius_direction += n.GetVelocity(); 

	}

	if (preception_radius_boid_count > 0){
		preception_radius_direction /= preception_radius_boid_count;
		steering = preception_radius_direction - velocity;

		// cout << "preception_radius_boid_count:" << preception_radius_boid_count << endl;
		// cout << "velocity:" << glm::to_string(velocity) << endl;
		// cout << "preception_radius_direction:" << glm::to_string(preception_radius_direction) << endl;
		// cout << "steering:" << glm::to_string(steering) << endl;
		// cout << "steering.length():" << steering.length() << endl;

		// Limit Steering
		if(glm::length(steering) > limit_aling_steering_mag)
			steering = glm::normalize(steering)*limit_aling_steering_mag;

	}

	// Update
	velocity += steering;
}

void Boid::Update(){
	
	ApplyLimits();
	
	position += velocity;
	velocity += acceleration;
}

void Boid::UpdatePositionToBounds(const glm::vec2& bounds){
	position.x = fmod(position.x+bounds.x,bounds.x);
	position.y = fmod(position.y+bounds.y,bounds.y);
}