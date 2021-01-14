#include <vector>
#include <iostream>
#include <Universe/Universe.cuh>

#include <chrono>
#include <time.h>

using namespace std;

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Universe::step() {
	long value_ms = timeSinceEpochMillisec();

	u_time.setData(value_ms - h_start_time);

	//cout << u_time.getData() << endl;
}

Universe::Universe(UniverseConfig& c) :
	h_camera(c.width,c.height) {

	long value_ms = timeSinceEpochMillisec();

		h_start_time = value_ms;
		u_time.setData(0);
		u_resolution.setData(vec2(c.width,c.height));

		l.u_time = u_time.getAddress();
		l.u_resolution = u_resolution.getAddress();

}

Universe::~Universe(){
}