#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <Grid/Grid.hpp>
#include <Display/Display.hpp>

using namespace std;

int main (int argc,char** argv) {

	int width = 1000;
	int height = 1000;

	Grid pattern(width,height);

	OpenCVWindowInit(&pattern);

	while(true) {
		pattern.step();
		OpenCVWindow();
		// usleep(1000*1000);
	}
	return 0;
}