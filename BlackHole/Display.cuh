#ifndef SIMULATION_BLACKHOLE_DISPLAY_
#define SIMULATION_BLACKHOLE_DISPLAY_

#include <Universe/Universe.cuh>

struct DisplayConfig {
	int width;
	int height;

	Universe* universe_obj;	
};

void OpenCVWindowInit(DisplayConfig& c);
void OpenCVWindow();

#endif /*SIMULATION_BLACKHOLE_DISPLAY_*/