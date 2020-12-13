#include <Boids/Boid.hpp>

#include <iostream>
#include <math.h>

using namespace std;

Boid::Boid(glm::vec2 position,glm::vec2 velocity,glm::vec2 acceleration) :

/* Magic Numbers */
	limit_velocity_mag(4.0f) , 
	limit_acceleration_mag(4.0f), 
	aling_steering_mag(2.0f),
	cohesion_steering_mag(0.1f),
/* End Magic Numbers */

	position(position),
	velocity(velocity),
	acceleration(acceleration)
	{
}

void Boid::Limit(glm::vec2& quantity,float limit_mag) {
	if(glm::length(quantity) > limit_mag) 
		quantity = glm::normalize(quantity)*limit_mag;
}

void Boid::SetMag(glm::vec2& quantity,float mag) {
	quantity = glm::normalize(quantity)*mag;
}


void Boid::Align(const std::vector<Boid*>& neighbours){

	glm::vec2 preception_radius_direction = glm::vec2(0.0f);
	glm::vec2 steering = glm::vec2(0.0f);

	for ( auto n : neighbours) {
		preception_radius_direction += n->GetVelocity(); 
	}

	if (neighbours.size() > 0){
		preception_radius_direction /= neighbours.size();
		steering = preception_radius_direction - velocity;

		// cout << "steering:" << glm::to_string(steering) << endl;

		SetMag(steering,aling_steering_mag);

	}

	// Update
	acceleration += steering;
}

void Boid::Cohesion(const std::vector<Boid*>& neighbours){

	glm::vec2 preception_radius_postion= glm::vec2(0.0f);
	glm::vec2 steering = glm::vec2(0.0f);

	for ( auto n : neighbours) {
		preception_radius_postion += n->GetPosition(); 
	}

	if (neighbours.size() > 0){
		preception_radius_postion /= neighbours.size();
		steering = preception_radius_postion - this->GetPosition();

		SetMag(steering,cohesion_steering_mag);
	}

	// Update
	acceleration += steering;
}

void Boid::Update(){
	
	Limit(velocity,limit_velocity_mag);
	Limit(acceleration,limit_acceleration_mag);
	
	position += velocity;
	velocity += acceleration;
}

void Boid::UpdatePositionToBounds(const glm::vec2& bounds){
	position.x = fmod(position.x+bounds.x,bounds.x);
	position.y = fmod(position.y+bounds.y,bounds.y);
}