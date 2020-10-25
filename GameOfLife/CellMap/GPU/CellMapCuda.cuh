#ifndef SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_CUDA_HPP_
#define SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_CUDA_HPP_

#include <vector>

#include <CellMap/CellMap.hpp>

class CellMapCuda : public CellMap {

private:
	bool* cells_gpu;
	bool* cells_gpu_temp;

public:
	CellMapCuda(int width, int height, bool edge_wrap);
	~CellMapCuda();

	void MakeCellAlive(int x, int y);
	void MakeCellDie(int x, int y);
	bool GetCell(int x, int y);

	void Step(int count);

};

#endif /*SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_CUDA_HPP_*/