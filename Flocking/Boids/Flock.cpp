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

	for (auto& b : boids) b.Align(preception_radius,boids);

	for (auto& b : boids) {
		b.Update();
		b.UpdatePositionToBounds(bounds);
	}
}
 	