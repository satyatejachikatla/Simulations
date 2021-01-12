#include <vector>
#include <iostream>
#include <Universe/Universe.cuh>

#include <time.h>

using namespace std;

void Universe::step() {
	long value_ms = time(0);

	u_time.setData(value_ms - h_start_time);
	//cout << u_time.getData() << endl;
}

Universe::Universe(UniverseConfig& c) :
	h_camera(c.width,c.height) {

	long value_ms = time(0);

		h_start_time = value_ms;
		u_time.setData(0);

		l.u_time = u_time.getAddress();

}

Universe::~Universe(){
}