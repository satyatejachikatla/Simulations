#pragma once

#include <vector>
#include <cstdint>

class Grid {
    private:
        int width;
        int height;

        std::vector<double> grid;

        int IDX(int row,int col);
    public:
        Grid(int width,int height);
        ~Grid(){}

        int getWidth(){return width;}
        int getHeight(){return height;}

        double getPixel(int row,int col){return grid[IDX(row,col)];}

        void step();

};