#include <iostream>
#include <vector>
#include <string>

#include <CellMap/CellMapFactory.hpp>
#include <ShellDisplay/ShellDisplay.hpp>
#include <OpenCVWindow/OpenCVWindow.hpp>

using namespace std;

void usage() {
	cout << "1: Implementation" << endl;
	cout << "\t(CPU,Cuda,CL)" << endl;
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

	void (*Display)(CellMap* ,CellMapFactoryConfig& ,int );

	if (imp != "Cuda" && imp != "CPU" && imp != "CL") {
		usage();
		return 0;
	}

	CellMapFactoryConfig config;
	config.implementation = imp;
	config.height = 1000;
	config.width = 1000;
	config.edge_wrap = true;
	
	CellMap* GameOfLife = CellMapFactory(config);

	if (display == "Shell") {
		Display = ShellDisplay;
	} else if (display == "CV"){
		OpenCVWindowInit(GameOfLife,config);
		Display = OpenCVWindow;
	}
	else {
		usage();
		return 0;
	} 

GameOfLife->MakeCellAlive( 13, 1);
GameOfLife->MakeCellAlive( 14, 2);
GameOfLife->MakeCellDie( 14, 2);
GameOfLife->MakeCellAlive( 13, 2);
GameOfLife->MakeCellAlive( 13, 3);
GameOfLife->MakeCellDie( 0 ,2);
GameOfLife->MakeCellAlive( 6 ,21);
GameOfLife->MakeCellAlive( 8 ,21);
GameOfLife->MakeCellDie( 8 ,21);
GameOfLife->MakeCellAlive( 7 ,21);
GameOfLife->MakeCellAlive( 6 ,22);
GameOfLife->MakeCellAlive( 7 ,22);
GameOfLife->MakeCellAlive( 8 ,23);
GameOfLife->MakeCellAlive( 9 ,23);
GameOfLife->MakeCellAlive( 10, 23);
GameOfLife->MakeCellAlive( 11, 23);
GameOfLife->MakeCellAlive( 12, 23);
GameOfLife->MakeCellAlive( 13, 23);
GameOfLife->MakeCellAlive( 14, 23);
GameOfLife->MakeCellAlive( 15, 23);
GameOfLife->MakeCellAlive( 16, 22);
GameOfLife->MakeCellAlive( 16, 21);
GameOfLife->MakeCellAlive( 16, 23);
GameOfLife->MakeCellDie( 15, 23);
GameOfLife->MakeCellAlive( 17, 20);
GameOfLife->MakeCellAlive( 19, 19);
GameOfLife->MakeCellAlive( 18, 19);
GameOfLife->MakeCellAlive( 18, 24);
GameOfLife->MakeCellDie( 18, 24);
GameOfLife->MakeCellAlive( 17, 24);
GameOfLife->MakeCellAlive( 18, 25);
GameOfLife->MakeCellAlive( 20, 25);
GameOfLife->MakeCellDie( 21, 25);
GameOfLife->MakeCellDie( 21, 25);
GameOfLife->MakeCellDie( 20, 25);
GameOfLife->MakeCellAlive( 19, 25);
GameOfLife->MakeCellAlive( 18, 22);
GameOfLife->MakeCellAlive( 17, 22);
GameOfLife->MakeCellAlive( 19, 22);
GameOfLife->MakeCellAlive( 20, 22);
GameOfLife->MakeCellDie( 19, 22);
GameOfLife->MakeCellDie( 19, 22);
GameOfLife->MakeCellDie( 18, 22);
GameOfLife->MakeCellDie( 17, 22);
GameOfLife->MakeCellDie( 14, 24);
GameOfLife->MakeCellDie( 13, 23);
GameOfLife->MakeCellDie( 10, 23);
GameOfLife->MakeCellDie( 11, 23);
GameOfLife->MakeCellDie( 14, 23);
GameOfLife->MakeCellDie( 12, 23);
GameOfLife->MakeCellDie( 9 ,23);
GameOfLife->MakeCellDie( 8 ,23);
GameOfLife->MakeCellAlive( 21, 21);
GameOfLife->MakeCellAlive( 21, 20);
GameOfLife->MakeCellDie( 21, 21);
GameOfLife->MakeCellAlive( 21, 23);
GameOfLife->MakeCellAlive( 21, 24);
GameOfLife->MakeCellDie( 21, 23);
GameOfLife->MakeCellAlive( 22, 21);
GameOfLife->MakeCellAlive( 22, 22);
GameOfLife->MakeCellAlive( 22, 23);
GameOfLife->MakeCellAlive( 23, 22);
GameOfLife->MakeCellAlive( 25, 22);
GameOfLife->MakeCellAlive( 26, 21);
GameOfLife->MakeCellDie( 25, 22);
GameOfLife->MakeCellAlive( 27, 21);
GameOfLife->MakeCellAlive( 26, 20);
GameOfLife->MakeCellAlive( 27, 20);
GameOfLife->MakeCellAlive( 26, 19);
GameOfLife->MakeCellAlive( 27, 19);
GameOfLife->MakeCellAlive( 28, 18);
GameOfLife->MakeCellAlive( 28, 22);
GameOfLife->MakeCellAlive( 30, 18);
GameOfLife->MakeCellAlive( 30, 16);
GameOfLife->MakeCellAlive( 30, 17);
GameOfLife->MakeCellDie( 30, 16);
GameOfLife->MakeCellAlive( 30, 22);
GameOfLife->MakeCellAlive( 31, 23);
GameOfLife->MakeCellDie( 31, 23);
GameOfLife->MakeCellAlive( 30, 23);
GameOfLife->MakeCellAlive( 31, 19);
GameOfLife->MakeCellAlive( 32, 19);
GameOfLife->MakeCellAlive( 33, 19);
GameOfLife->MakeCellAlive( 34, 19);
GameOfLife->MakeCellAlive( 35, 19);
GameOfLife->MakeCellAlive( 36, 19);
GameOfLife->MakeCellAlive( 37, 19);
GameOfLife->MakeCellAlive( 38, 19);
GameOfLife->MakeCellAlive( 39, 19);
GameOfLife->MakeCellAlive( 40, 19);
GameOfLife->MakeCellAlive( 41, 19);
GameOfLife->MakeCellAlive( 41, 20);
GameOfLife->MakeCellAlive( 40, 20);
GameOfLife->MakeCellDie( 39, 19);
GameOfLife->MakeCellDie( 39, 19);
GameOfLife->MakeCellDie( 38, 19);
GameOfLife->MakeCellDie( 37, 19);
GameOfLife->MakeCellDie( 36, 19);
GameOfLife->MakeCellDie( 35, 19);
GameOfLife->MakeCellDie( 34, 19);
GameOfLife->MakeCellDie( 34, 19);
GameOfLife->MakeCellDie( 33, 19);
GameOfLife->MakeCellDie( 32, 19);
GameOfLife->MakeCellDie( 32, 19);
GameOfLife->MakeCellDie( 31, 19);

	while(true) {
		Display(GameOfLife,config,1);
	}
	return 0;

	delete GameOfLife;
}