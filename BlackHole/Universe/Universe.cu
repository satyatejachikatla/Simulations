#include <vector>
#include <Universe/Universe.cuh>


void Universe::step() {

}

Universe::Universe(UniverseConfig& c) :
	h_camera(c.width,c.height) {
}

Universe::~Universe(){
	
}
