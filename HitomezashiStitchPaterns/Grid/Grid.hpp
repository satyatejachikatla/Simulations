#pragma once

#include <vector>
#include <cstdint>

struct Cell {
    bool topStitch;
    bool leftStitch;
    int color;

    bool visited;

    int row;
    int col;
    std::vector<Cell*> adjCells;
};

class Grid {
    private:
        int width;
        int height;

        std::vector<Cell> grid;

        void fillVertical();
        void fillHorizontal();
        void fillColor();
        void fillColorHelper(Cell* c,int color);
        void populateAdjLists();

        int IDX(int row,int col);

        void resetVisited();
    public:
        Grid(int width,int height);
        ~Grid(){}

        int getWidth(){return width;}
        int getHeight(){return height;}

        void printGridLeft();
        void printGridTop();
        int getPixel(int row,int col){return grid[IDX(row,col)].color;}

        bool getTopStitch(int row,int col);
        bool getLeftStitch(int row,int col);
        bool getBottomStitch(int row,int col);
        bool getRightStitch(int row,int col);

        void step();

};