#include <vector>
#include <iostream>
#include <CellMap/GPU/CellMapCuda.cuh>
#include <CudaErrors.cuh>
#include <cmath>

using namespace std;

#define MAX_THREADS_IN_AXIS 32.0

__host__ __device__ inline int mod(int value,int m) {
	int modulo = value % m;
	if (modulo < 0) modulo += m;

	return modulo;
}

#define IDX(a,b)  mod((a),width) + mod((b),height) * width

__device__ bool IsInbounds(int x,int y,int width,int height,bool edge_wrap) {
	if(edge_wrap) return true;
	return (0 <= x  && x < width && 0 <= y && y < height);
}

__device__ int CellMapCudaGetNeighbourCount(bool* cells_gpu,int x,int y,int width,int height,bool edge_wrap) {

	int count=0;

	if ( IsInbounds(x-1,y-1,width,height,edge_wrap) ) count += cells_gpu[IDX(x-1,y-1)];
	if ( IsInbounds(x-1,y,width,height,edge_wrap)   ) count += cells_gpu[IDX(x-1,y)];
	if ( IsInbounds(x-1,y+1,width,height,edge_wrap) ) count += cells_gpu[IDX(x-1,y+1)];
	if ( IsInbounds(x,y-1,width,height,edge_wrap)   ) count += cells_gpu[IDX(x,y-1)];
	if ( IsInbounds(x,y+1,width,height,edge_wrap)   ) count += cells_gpu[IDX(x,y+1)];
	if ( IsInbounds(x+1,y-1,width,height,edge_wrap) ) count += cells_gpu[IDX(x+1,y-1)];
	if ( IsInbounds(x+1,y,width,height,edge_wrap)   ) count += cells_gpu[IDX(x+1,y)];
	if ( IsInbounds(x+1,y+1,width,height,edge_wrap) ) count += cells_gpu[IDX(x+1,y+1)];

	return count;
}


__global__ void CellMapCudaStep(bool* cells_gpu,bool* cells_gpu_temp,int width,int height,bool edge_wrap) {
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	int j = blockIdx.y*blockDim.y + threadIdx.y;

	if(i >= width || j >= height) return;

	int index = IDX(i,j);

	int neighbours_alive_count = CellMapCudaGetNeighbourCount(cells_gpu,i,j,width,height,edge_wrap);

	switch(neighbours_alive_count) {
		case 0 :
		case 1 : cells_gpu_temp[index] = false; break;
		case 2 : cells_gpu_temp[index] = cells_gpu[index]; break;
		case 3 : cells_gpu_temp[index] = true; break;
		case 4 :
		case 5 : 
		case 6 :
		case 7 :
		case 8 : cells_gpu_temp[index] = false; break;
	}

}

CellMapCuda::CellMapCuda(int width, int height, bool edge_wrap) :
	CellMap(width,height,edge_wrap) {
		checkCudaErrors(cudaMallocManaged((void **)&cells_gpu, height*width*sizeof(*cells_gpu)));
		checkCudaErrors(cudaMallocManaged((void **)&cells_gpu_temp, height*width*sizeof(*cells_gpu_temp)));

		checkCudaErrors(cudaMemset(cells_gpu,0,height*width*sizeof(*cells_gpu)));
		checkCudaErrors(cudaMemset(cells_gpu_temp,0,height*width*sizeof(*cells_gpu_temp)));
}
CellMapCuda::~CellMapCuda(){
	checkCudaErrors(cudaFree(cells_gpu));
	checkCudaErrors(cudaFree(cells_gpu_temp));
}


void CellMapCuda::Step(int step_count) {

	dim3 blocks(ceil(width/MAX_THREADS_IN_AXIS),ceil(height/MAX_THREADS_IN_AXIS));
	dim3 threads(MAX_THREADS_IN_AXIS,MAX_THREADS_IN_AXIS);

	bool* t;

	for(int c=0;c<step_count;c++) {
		CellMapCudaStep<<<blocks,threads>>>(cells_gpu,cells_gpu_temp,width,height,edgeWrap);
		checkCudaErrors(cudaGetLastError());
		checkCudaErrors(cudaDeviceSynchronize());
		t = cells_gpu;
		cells_gpu = cells_gpu_temp;
		cells_gpu_temp = t;
	}

}

void CellMapCuda::MakeCellAlive(int x, int y) {
	CellMap::MakeCellAlive(x,y);
	cells_gpu[IDX(x,y)] = true;
}

void CellMapCuda::MakeCellDie(int x, int y) {
	CellMap::MakeCellDie(x,y);
	cells_gpu[IDX(x,y)] = false;
}

bool CellMapCuda::GetCell(int x, int y){
	(*cells)[IDX(x,y)] = cells_gpu[IDX(x,y)];
	return (*cells)[IDX(x,y)];
}