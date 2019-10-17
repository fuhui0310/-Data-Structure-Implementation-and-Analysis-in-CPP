#ifndef FUMAZEGENERATOR_HPP
#define FUMAZEGENERATOR_HPP
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include "Direction.hpp"
#include <random>

class FuMazeGenerator: public MazeGenerator
{
public:
	FuMazeGenerator();
    virtual void generateMaze(Maze& maze);
    void generateCall(int x, int y, Maze& maze);
    std::vector<int> directions(int x, int y);

private:
	std::vector<std::vector<bool>> passed;
	std::random_device device;
	std::default_random_engine engine{device()};
	int w;
	int h;
};



#endif