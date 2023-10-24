#include <Grid/Grid.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

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
    grid.resize((this->width)*(this->height),0);
}


void Grid::step() {
    static int timePrescaled = 0;

    for (int steps=0;steps<500;steps++)
    {
        double scale = .125;
        double t = timePrescaled*.0001;

        double x_component = (cos(t) + cos(PI*t))*scale;
        double y_component = (sin(t) + sin(PI*t))*scale;

        int i = y_component*height +.5*height;
        int j = x_component*width +.5*height;

        grid[IDX(i,j)] = 1;

        timePrescaled++;
    }
}