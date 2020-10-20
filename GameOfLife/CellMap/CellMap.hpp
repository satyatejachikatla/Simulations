#pragma once

#include <vector>

using namespace std;

int mod(int value,int m);

class CellMap {

private:

	vector<bool>* temp_state;
	bool EdgeWrap;

	bool isInbounds(int x,int y);

	int width;
	int height;

public:

	vector<bool>* curr_state;

	CellMap()=delete;
	CellMap(int width, int height, bool EdgeWrap);

	void makeCellAlive(int x, int y);
	void makeCellDie(int x, int y);
	int getNeighboursAliveCount(int x, int y);
	void step();

};
