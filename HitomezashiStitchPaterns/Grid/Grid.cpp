#include <Grid/Grid.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>

int Grid::IDX(int row,int col){ 
    row = row % height;
    col = col % width;

    if(row < 0)
        row = row + height;
    if(col < 0)
        col = col + width;

    return (row*(width) + col);
}

Grid::Grid(int width,int height){
    this->width = width;
    this->height = height;
    grid.resize((this->width)*(this->height));

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            grid[IDX(i,j)].row = i;
            grid[IDX(i,j)].col = j;
        }
    }
}


bool Grid::getTopStitch(int row,int col){
    if( row < 0 || row >= width ||
        col < 0 || col >= height)
        return true;
    return grid[IDX(row,col)].topStitch;
}
bool Grid::getLeftStitch(int row,int col){
    if( row < 0 || row >= width ||
        col < 0 || col >= height)
        return true;
    return grid[IDX(row,col)].leftStitch;
}
bool Grid::getBottomStitch(int row,int col){
    if( row < 0 || row >= width ||
        col < 0 || col >= height)
        return true;
    return grid[IDX(row+1,col)].topStitch;
}
bool Grid::getRightStitch(int row,int col){
    if( row < 0 || row >= width ||
        col < 0 || col >= height)
        return true;
    return grid[IDX(row,col+1)].leftStitch;
}

void Grid::step() {
    fillVertical();
    fillHorizontal();
    fillColor();
}

void Grid::fillVertical(){
    for(int j=0;j<width;j++){
        int toggle = rand() % 2;
        for(int i=0;i<height;i++){    
            grid[IDX(i,j)].leftStitch = toggle;
            toggle = (toggle + 1) % 2;
        }
    }
}
void Grid::fillHorizontal(){
    for(int i=0;i<height;i++){
        int toggle = rand() % 2;
        for(int j=0;j<width;j++){
            grid[IDX(i,j)].topStitch = toggle;
            toggle = (toggle + 1) % 2;
        }
    }
}

void Grid::populateAdjLists(){
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            grid[IDX(i,j)].adjCells.clear();
            if (!getLeftStitch(i,j))
                grid[IDX(i,j)].adjCells.push_back(&grid[IDX(i,j-1)]);
            if (!getRightStitch(i,j))
                grid[IDX(i,j)].adjCells.push_back(&grid[IDX(i,j+1)]);
            if (!getTopStitch(i,j))
                grid[IDX(i,j)].adjCells.push_back(&grid[IDX(i-1,j)]);
            if (!getBottomStitch(i,j))
                grid[IDX(i,j)].adjCells.push_back(&grid[IDX(i+1,j)]);
        }
    }
}

void Grid::fillColorHelper(Cell* currCell,int color){
    if(currCell->visited)
        return;
    currCell->color = color;
    currCell->visited = true;
    for(Cell* cell : currCell->adjCells){
        fillColorHelper(cell,color);
    }
}

void Grid::fillColor(){
    resetVisited();
    populateAdjLists();

    int color = 0;
    for(Cell& c : grid){
        if(!c.visited){
            // std::cout << "HEre" << c.row << " " <<c.col << std::endl;
            fillColorHelper(&c,color);
            color = (color + 1) %8;
        }
    }
    // std::cout << "----------------" << std::endl;
    // printGridLeft();
    // std::cout << "----------------" << std::endl;
    // printGridTop();
    // std::cout << "----------------" << std::endl;
}

void Grid::resetVisited(){
    for(Cell& c : grid){
        c.visited = false;
    }
}

void Grid::printGridLeft() {
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            std::cout << grid[IDX(i,j)].leftStitch << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::printGridTop() {
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            std::cout << grid[IDX(i,j)].topStitch << " ";
        }
        std::cout << std::endl;
    }
}