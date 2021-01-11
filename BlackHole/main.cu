#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <Universe/Universe.cuh>
#include <Display.cuh>

using namespace std;

int main (int argc,char** argv) {

	DisplayConfig disp_config;
	UniverseConfig u_config;

	disp_config.width = u_config.width = 100;
	disp_config.height = u_config.height = 100;

	Universe MyWorld(u_config);

	disp_config.universe_obj = &MyWorld;

	OpenCVWindowInit(disp_config);

	while(true) {
		MyWorld.step();
		OpenCVWindow();
		usleep(1000*100); // Frame Rate Limiter
	}
	return 0;
}