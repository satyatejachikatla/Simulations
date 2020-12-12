#include <Boids/Boid.hpp>

Boid::Boid(glm::vec2 position,glm::vec2 velocity,glm::vec2 acceleration) {
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
}

void Boid::Update(){
	position += velocity;
	velocity += acceleration;
}