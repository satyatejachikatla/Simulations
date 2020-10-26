#include <vector>
#include <iostream>
#include <CellMap/CPU/CellMapCPU.hpp>

using namespace std;

CellMapCPU::CellMapCPU(int width, int height, bool edge_wrap) :
	CellMap(width,height,edge_wrap) {
		temp_cells = new vector<uint8_t>();
		temp_cells->resize(width*height,0);
}
CellMapCPU::~CellMapCPU(){
	delete temp_cells;
}

void CellMapCPU::Step(int step_count) {

	for(int c=0; c<step_count ; c++) {
		for(int j=0; j < height ; j++) {
			for(int i=0; i < width ; i++) {
				int neighbours_alive_count = GetNeighboursAliveCount(i,j);
				int index=GetCellIndex(i,j);

				switch(neighbours_alive_count) {
				case 0 :
				case 1 : (*temp_cells)[index] = false; break;
				case 2 : (*temp_cells)[index] = (*cells)[index]; break;
				case 3 : (*temp_cells)[index] = true; break;
				case 4 :
				case 5 : 
				case 6 :
				case 7 :
				case 8 : (*temp_cells)[index] = false; break;
				}
			}
		}

		vector<uint8_t>* t;

		t = temp_cells;
		temp_cells = cells;
		cells = t;
	}
}