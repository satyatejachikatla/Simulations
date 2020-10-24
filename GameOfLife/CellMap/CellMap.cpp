#include <iostream>
#include <CellMap/CellMap.hpp>

using namespace std;

inline int mod(int value,int m) {
	int modulo = value % m;
	if (modulo < 0) modulo += m;

	return modulo;
}

#define IDX(a,b)  mod((a),width) + mod((b),height) * width

bool CellMap::IsInbounds(int x,int y) {
	if(edgeWrap) return true;
	return (0 <= x  && x < width && 0 <= y && y < height);
}

CellMap::CellMap(int width, int height,bool edge_wrap) : 
	width(width),
	height(height),
	edgeWrap(edge_wrap) {

	cells = new vector<bool>();
	cells->resize(width*height,0);
}

void CellMap::MakeCellAlive(int x, int y) {
	(*cells)[IDX(x,y)] = true;
}

void CellMap::MakeCellDie(int x, int y) {
	(*cells)[IDX(x,y)] = false;
}

bool CellMap::GetCell(int x, int y) {
	return (*cells)[IDX(x,y)];
}

int CellMap::GetCellIndex(int i,int j){
	return IDX(i,j);
}

int CellMap::GetNeighboursAliveCount(int x, int y) {
	int count = 0;

	if ( IsInbounds(x-1,y-1) ) count += (*cells)[IDX(x-1,y-1)];
	if ( IsInbounds(x-1,y)   ) count += (*cells)[IDX(x-1,y)];
	if ( IsInbounds(x-1,y+1) ) count += (*cells)[IDX(x-1,y+1)];
	if ( IsInbounds(x,y-1)   ) count += (*cells)[IDX(x,y-1)];
	if ( IsInbounds(x,y+1)   ) count += (*cells)[IDX(x,y+1)];
	if ( IsInbounds(x+1,y-1) ) count += (*cells)[IDX(x+1,y-1)];
	if ( IsInbounds(x+1,y)   ) count += (*cells)[IDX(x+1,y)];
	if ( IsInbounds(x+1,y+1) ) count += (*cells)[IDX(x+1,y+1)];

	return count;
}

