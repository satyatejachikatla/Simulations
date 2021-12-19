#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <Grid/Grid.hpp>
#include <Display/Display.hpp>

using namespace std;

int main (int argc,char** argv) {

	int width = 100;
	int height = 100;

	Grid stitchPattern(width,height);

	OpenCVWindowInit(&stitchPattern);

	while(true) {
		stitchPattern.step();
		OpenCVWindow();
		usleep(1000*1000);
	}
	return 0;
}