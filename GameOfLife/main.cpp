#include <iostream>
#include <vector>
#include <unistd.h>

#include <CellMap/CellMapFactory.hpp>

using namespace std;

void display(CellMap* GameOfLife,CellMapFactoryConfig& config) {

	for(int j=0; j < config.height ; j++) {
		for(int i=0; i < config.width ; i++) {
			cout << GameOfLife->GetCell(i,j) << " ";
		}
		cout << endl;
	}
	cout << "--------------------" << endl;

}

int main () {

	CellMapFactoryConfig config;
	config.implementation = "Cuda";
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
		display(GameOfLife,config);
		GameOfLife->Step(1);
		sleep(1);
	}
	return 0;

	delete GameOfLife;
}