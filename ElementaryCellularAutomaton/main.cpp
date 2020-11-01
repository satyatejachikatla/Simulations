#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <ElementaryCells/ElementaryCells.hpp>
#include <Display.hpp>

using namespace std;

int main (int argc,char** argv) {

	int width = 100;
	int height = 100;
	std::vector<bool> rule{0,1,1,1,1,0,0,0}; // Rule 30
//	std::vector<bool> rule{1,0,1,1,0,1,0,0}; // Rule 45
//	std::vector<bool> rule{0,1,0,1,1,0,1,0}; // Rule 90

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