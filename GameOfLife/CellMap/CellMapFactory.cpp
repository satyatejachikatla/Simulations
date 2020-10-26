#include <CellMap/CellMapFactory.hpp>

using namespace std;

CellMap* CellMapFactory(CellMapFactoryConfig& config) {

	if (config.implementation == "CPU") {
		return new CellMapCPU(config.height,config.width,config.edge_wrap);
	} else 	if (config.implementation == "Cuda") {
		return new CellMapCuda(config.height,config.width,config.edge_wrap);
	} else 	if (config.implementation == "CL") {
		return new CellMapOpenCL(config.height,config.width,config.edge_wrap);
	}

	return nullptr;
}