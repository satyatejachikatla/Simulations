#ifndef SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_OPENCL_HPP_
#define SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_OPENCL_HPP_

#include <vector>

#include <OpenCLCompileUtils.hpp>
#include <CellMap/CellMap.hpp>

#define CELLMAP_OPENCL_PROGRAM "./kernels/CellMapOpenCL.cl"

class CellMapOpenCL : public CellMap {

private:
	cl::Program program;
	cl::Kernel kernel;
	cl::Context context;
	cl::Device device;

	cl::Buffer cells_gpu;
	cl::Buffer cells_gpu_temp;

public:
	CellMapOpenCL(int width, int height, bool edge_wrap);
	~CellMapOpenCL();

	void Step(int count);

};

#endif /*SIMULATION_GAME_OF_LIFE_CELL_MAP_CELL_MAP_OPENCL_HPP_*/