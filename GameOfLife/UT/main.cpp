#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <CellMap/CellMapFactory.hpp>
#include <ShellDisplay/ShellDisplay.hpp>
#include <OpenCVWindow/OpenCVWindow.hpp>

using namespace std;

void usage() {
	cout << "1: Implementation" << endl;
	cout << "\t(CPU,Cuda)" << endl;
	cout << "2: Display" << endl;
	cout << "\t(Shell,CV)" << endl;
}

int main (int argc,char** argv) {

	if (argc < 3){
		usage();
		return 0;
	}

	string imp = argv[1];
	string display = argv[2];

	void (*Display)(CellMap* GameOfLife,CellMapFactoryConfig& config);

	if (imp != "Cuda" && imp != "CPU") {
		usage();
		return 0;
	}

	if (display == "Shell") {
		Display = ShellDisplay;
	} else if (display == "CV"){

	}
	else {
		usage();
		return 0;
	} 


	CellMapFactoryConfig config;
	config.implementation = imp;
	config.height = 10;
	config.width = 10;
	config.edge_wrap = true;
	
	CellMap* GameOfLife = CellMapFactory(config);

	GameOfLife->MakeCellAlive(2,1);
	GameOfLife->MakeCellAlive(2,2);
	GameOfLife->MakeCellAlive(2,3);
	GameOfLife->MakeCellAlive(1,3);
	GameOfLife->MakeCellAlive(0,2);

	while(true) {
		Display(GameOfLife,config);
		GameOfLife->Step(1);
		sleep(1);
	}
	return 0;

	delete GameOfLife;
}