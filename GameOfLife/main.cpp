#include <iostream>
#include <vector>
#include <CellMap/CellMap.hpp>
#include <unistd.h>

using namespace std;

#define IDX(a,b)  ((a)) + ((b)) * width

int width=10;
int height=10;

void display(CellMap& GameOfLife) {

	for(int j=0; j < height ; j++) {
		for(int i=0; i < width ; i++) {
			cout << (*GameOfLife.curr_state)[IDX(i,j)] << " ";
		}
		cout << endl;
	}
	cout << "--------------------" << endl;

}

int main () {

	CellMap GameOfLife(width,height);
	
	GameOfLife.makeCellAlive(2,1);
	GameOfLife.makeCellAlive(2,2);
	GameOfLife.makeCellAlive(2,3);
	GameOfLife.makeCellAlive(1,3);
	GameOfLife.makeCellAlive(0,2);
	display(GameOfLife);

	while(true) {
		GameOfLife.step();
		display(GameOfLife);
		sleep(1);
	}
	return 0;
}