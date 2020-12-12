#include <Boids/Flock.hpp>

Flock::Flock(int number_of_boids,int width,int height) :
	width(width),height(height) {
	for(int i=0;i<number_of_boids;i++) boids.push_back(
		Boid({0,0},{0,0},{0,0})
	);
}

void Flock::Update() {
}