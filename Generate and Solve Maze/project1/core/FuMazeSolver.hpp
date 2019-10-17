#ifndef FUMAZESOLVER_HPP
#define FUMAZESOLVER_HPP
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <vector>

class FuMazeSolver: public MazeSolver
{
public:
	FuMazeSolver();
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	void solveCall(int x, int y, const Maze& maze, MazeSolution& mazeSolution);
    std::vector<int> directions(int x, int y, const Maze& maze);

private:
	std::vector<std::vector<bool>> passed;
	int w;
	int h;

};



#endif