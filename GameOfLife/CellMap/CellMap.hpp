#pragma once

#include <vector>

using namespace std;

class CellMap {

private:

	vector<bool>* temp_state;

	bool isInbounds(int x,int y);

public:

	vector<bool>* curr_state;
	int width;
	int height;

	CellMap()=delete;

	CellMap(int width, int height);

	void makeCellAlive(int x, int y);
	void makeCellDie(int x, int y);
	int getNeighboursAliveCount(int x, int y);
	void step();

};
