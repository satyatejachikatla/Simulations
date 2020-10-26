int mod(int value,int m) {
	int modulo = value % m;
	if (modulo < 0) modulo += m;

	return modulo;
}

#define IDX(a,b)  mod((a),width) + mod((b),height) * width

bool IsInbounds(int x,int y,int width,int height,bool edge_wrap) {
	if(edge_wrap) return true;
	return (0 <= x  && x < width && 0 <= y && y < height);
}

int CellMapOpenCLGetNeighbourCount(__global bool* cells_gpu,int x,int y,int width,int height,bool edge_wrap) {

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

__kernel void CellMapOpenCLStep(__global bool* cells_gpu,__global bool* cells_gpu_temp,int width,int height,char edge_wrap) {
	
	int i = get_group_id(0) * get_local_size(0) + get_local_id(0);
	int j = get_group_id(1) * get_local_size(1) + get_local_id(1);

	if(i >= width || j >= height) return;

	int index = IDX(i,j);

	int neighbours_alive_count = CellMapOpenCLGetNeighbourCount(cells_gpu,i,j,width,height,edge_wrap);

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