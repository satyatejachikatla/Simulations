#ifndef SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_CPU_HPP_
#define SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_CPU_HPP_

#include <vector>

#include <CellMap/CellMap.hpp>

class CellMapCPU : public CellMap {

private:

	std::vector<uint8_t>* temp_cells;	

public:
	CellMapCPU(int width, int height, bool edge_wrap);
	~CellMapCPU();
	void Step(int count);

};

#endif /*SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_CPU_HPP_*/