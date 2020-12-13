#include <Boids/Flock.hpp>

#include <stdlib.h>
#include <glm/gtc/random.hpp>

Flock::Flock(int number_of_boids,int width,int height) :
	bounds({width ,height}) {
	for(int i=0;i<number_of_boids;i++) boids.push_back(
		Boid(
				glm::vec2(rand()%width,rand()%height),	// Initializing random in window
				glm::circularRand(1.0f),				// Random unit velocity
				{0.0f,0.0f}								// 0 initial acceleration
			)
	);
}

void Flock::Update() {

	for (auto& b : boids){
		std::vector<Boid*> neighbour_boids = GetNeighbourBoidsTo(b); 

		b.ClearAcceleration();

		b.Align(neighbour_boids);
		b.Cohesion(neighbour_boids);
	}

	for (auto& b : boids) {
		b.Update();
		b.UpdatePositionToBounds(bounds);
	}
}


std::vector<Boid*> Flock::GetNeighbourBoidsTo(Boid& boid) {

	std::vector<Boid*> ret;

	for ( auto& n : boids) {
		if ( &n == &boid ) continue;

		glm::vec2 p1 = n.GetPosition();
		glm::vec2 p2 = boid.GetPosition();

		float dist_btwn_boids = glm::distance(p1,p2);

		if(dist_btwn_boids > preception_radius) continue;

		ret.push_back(&n);
	}

	return ret;
}