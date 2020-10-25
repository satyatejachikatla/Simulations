#include <iostream>
#include <ShellDisplay/ShellDisplay.hpp>

using namespace std;

void ShellDisplay(CellMap* GameOfLife,CellMapFactoryConfig& config) {

	for(int j=0; j < config.height ; j++) {
		for(int i=0; i < config.width ; i++) {
			cout << GameOfLife->GetCell(i,j) << " ";
		}
		cout << endl;
	}
	cout << "--------------------" << endl;

}