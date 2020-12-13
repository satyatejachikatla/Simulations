#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>


#include <Boids/Flock.hpp>
#include <Display.hpp>

int main (int argc,char** argv) {

	int width = 100;
	int height = 100;

	Flock flock(50,width,height);

	OpenCVWindowInit(flock);

	while(true) {
		flock.Update();
		OpenCVWindow();
		usleep(100000);
	}
	return 0;
}