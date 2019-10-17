#include <ics46/factory/DynamicFactory.hpp>
#include "FuMazeSolver.hpp"
#include "Direction.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, FuMazeSolver,"Fu's MazeSolver(Required)");

FuMazeSolver::FuMazeSolver(){}

void FuMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
	mazeSolution.restart();
	w = maze.getWidth();
	h = maze.getHeight();
	std::vector<bool> v(h);
	for(int i = 0; i < w; i++){
		passed.push_back(v);
	}
	int i = mazeSolution.getStartingCell().first;
	int j = mazeSolution.getStartingCell().second;
	solveCall(i, j, maze, mazeSolution);
}

void FuMazeSolver::solveCall(int x, int y, const Maze& maze, MazeSolution& mazeSolution){
	passed[x][y] = true;
	if(mazeSolution.isComplete()){
		return;
	}
	std::vector<int> available = directions(x, y, maze);
	int count = available.size();
	int n;
	for(int i = 0; i < count; i++){
		n = available.at(i);
		std::vector<Direction> current = mazeSolution.getMovements();
		switch(n){
			case 1:
					mazeSolution.extend(Direction::up);
					solveCall(x, y-1, maze, mazeSolution);
					break;
			case 2:
					mazeSolution.extend(Direction::down);
					solveCall(x, y+1, maze, mazeSolution);
					break;
			case 3:
					mazeSolution.extend(Direction::left);
					solveCall(x-1, y, maze, mazeSolution);
					break;
			case 4:
					mazeSolution.extend(Direction::right);
					solveCall(x+1, y, maze, mazeSolution);
					break;
		}
		if(mazeSolution.isComplete()){
			break;
		}
		if(count > 1){
			mazeSolution.replace(current);
		}
		
	}
	return;
}

std::vector<int> FuMazeSolver::directions(int x, int y, const Maze &maze){
	std::vector<int> a;

	if(( y+1 <= h-1 && passed[x][y+1] != true && maze.wallExists(x, y, Direction::down) == false)){
		a.push_back(2);
	}
	if(( x+1 <= w-1 && passed[x+1][y] != true && maze.wallExists(x, y, Direction::right) == false)){
		a.push_back(4);
	}
	if(( y-1 >= 0 && passed[x][y-1] != true && maze.wallExists(x, y, Direction::up) == false)){
		a.push_back(1);
	}
	if(( x-1 >= 0 && passed[x-1][y] != true && maze.wallExists(x, y, Direction::left) == false)){
		a.push_back(3);
	}
	return a;
}

