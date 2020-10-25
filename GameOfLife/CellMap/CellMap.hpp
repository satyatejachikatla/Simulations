#ifndef SIMULATION_GAME_OF_LIFE_CELL_MAP_HPP_
#define SIMULATION_GAME_OF_LIFE_CELL_MAP_HPP_

#include <vector>

class CellMap {

protected:

	int width;
	int height;
	bool edgeWrap;

	std::vector<bool>* cells;

	bool IsInbounds(int x,int y);
	int GetCellIndex(int i,int j);

public:

	CellMap()=delete;

	CellMap(int width, int height, bool edge_wrap);
	virtual ~CellMap();

	virtual void MakeCellAlive(int x, int y);
	virtual void MakeCellDie(int x, int y);

	virtual bool GetCell(int x, int y);
	int GetNeighboursAliveCount(int x, int y);

	virtual void Step(int count) = 0;

};

#endif /*SIMULATION_GAME_OF_LIFE_CELL_MAP_HPP_*/