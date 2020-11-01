#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <ElementaryCells/ElementaryCells.hpp>
#include <Display.hpp>

using namespace std;

int main (int argc,char** argv) {

	int width = 50;
	int height = 50;
	std::vector<bool> rule{0,1,1,1,1,0,0,0}; // Rule 30

	ElementaryCells Wolfman(rule,width,true);
	std::vector<bool> buff(width);

	OpenCVWindowInit(width,height);

	while(true) {
		Wolfman.Step(1,buff);
		OpenCVWindow(buff);
		usleep(1000*100);
	}
	return 0;
}