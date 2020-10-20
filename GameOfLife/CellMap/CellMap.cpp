#include "CellMap.hpp"
#include <iostream>

int mod(int value,int m) {
	int modulo = value % m;
	if (modulo < 0) modulo += m;

	return modulo;
}

#define IDX(a,b)  mod((a),width) + mod((b),height) * width

using namespace std;

bool CellMap::isInbounds(int x,int y) {
	if(EdgeWrap) return true;
	return (0 <= x  && x < width && 0 <= y && y < height);
}

CellMap::CellMap(int width, int height,bool EdgeWrap) {
	this->width = width;
	this->height = height;
	this->EdgeWrap = EdgeWrap;

	temp_state = new vector<bool>();
	curr_state = new vector<bool>();

	temp_state->resize(width*height,0);
	curr_state->resize(width*height,0);
}

void CellMap::makeCellAlive(int x, int y) {
	(*curr_state)[IDX(x,y)] = true;
}

void CellMap::makeCellDie(int x, int y) {
	(*curr_state)[IDX(x,y)] = false;
}

int CellMap::getNeighboursAliveCount(int x, int y) {
	int count = 0;

	if ( isInbounds(x-1,y-1) ) count += (*curr_state)[IDX(x-1,y-1)];
	if ( isInbounds(x-1,y)   ) count += (*curr_state)[IDX(x-1,y)];
	if ( isInbounds(x-1,y+1) ) count += (*curr_state)[IDX(x-1,y+1)];
	if ( isInbounds(x,y-1)   ) count += (*curr_state)[IDX(x,y-1)];
	if ( isInbounds(x,y+1)   ) count += (*curr_state)[IDX(x,y+1)];
	if ( isInbounds(x+1,y-1) ) count += (*curr_state)[IDX(x+1,y-1)];
	if ( isInbounds(x+1,y)   ) count += (*curr_state)[IDX(x+1,y)];
	if ( isInbounds(x+1,y+1) ) count += (*curr_state)[IDX(x+1,y+1)];

	return count;
}

void CellMap::step() {

	for(int j=0; j < height ; j++) {
		for(int i=0; i < width ; i++) {
			int neighboursAliveCount = getNeighboursAliveCount(i,j);
			int index=IDX(i,j);

			switch(neighboursAliveCount) {
			case 0 :
			case 1 : (*temp_state)[index] = false; break;
			case 2 : (*temp_state)[index] = (*curr_state)[index]; break;
			case 3 : (*temp_state)[index] = true; break;
			case 4 :
			case 5 : 
			case 6 :
			case 7 :
			case 8 : (*temp_state)[index] = false; break;
			}
		}
	}

	vector<bool>* t;

	t = temp_state;
	temp_state = curr_state;
	curr_state = t;

}

