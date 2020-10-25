#ifndef SIMULATION_GAME_OF_LIFE_OPENCV_WINDOW_DISPLAY_HPP_
#define SIMULATION_GAME_OF_LIFE_OPENCV_WINDOW_DISPLAY_HPP_

#include <CellMap/CellMapFactory.hpp>

void OpenCVWindow(CellMap* GameOfLife,CellMapFactoryConfig& config,int step);
void OpenCVWindowInit(CellMap* GameOfLife,CellMapFactoryConfig& config);

#endif /*SIMULATION_GAME_OF_LIFE_OPENCV_WINDOW_DISPLAY_HPP_*/