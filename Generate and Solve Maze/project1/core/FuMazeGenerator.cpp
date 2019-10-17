#include <ics46/factory/DynamicFactory.hpp>
#include "FuMazeGenerator.hpp"
//#include "Direction.hpp"
//#include "iostream"
//#include <algorithm>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, FuMazeGenerator, "Fu's MazeGenerator(Required)");

FuMazeGenerator::FuMazeGenerator(){}

void FuMazeGenerator::generateMaze(Maze& maze){
	maze.addAllWalls();
	w = maze.getWidth();
	h = maze.getHeight();
	std::vector<bool> v(h);
	for(int i = 0; i < w; i++){
		passed.push_back(v);
	}
	generateCall(0, 0, maze);
}

void FuMazeGenerator::generateCall(int x, int y, Maze& maze){
	passed[x][y] = true;
	int n;
	Direction d;
	std::vector<int> available = directions(x, y);
	int count = available.size();
	while(count > 0){
		std::uniform_int_distribution<int> distribution{1,count};
		n = available.at(distribution(engine) - 1);
		switch(n){
			case 1:
					d = Direction::up;
					generateCall(x, y-1, maze);
					break;
			case 2:
					d = Direction::down;
					generateCall(x, y+1, maze);
					break;
			case 3:
					d = Direction::left;
					generateCall(x-1, y, maze);
					break;
			case 4:
					d = Direction::right;
					generateCall(x+1, y, maze);
					break;
		}
		maze.removeWall(x, y, d);
		available = directions(x, y);
		count = available.size();
	}
	return;
}


std::vector<int> FuMazeGenerator::directions(int x, int y){
	std::vector<int> a;
	if(( y-1 >= 0 && passed[x][y-1] != true)){
		a.push_back(1);
	}
	if(( y+1 <= h-1 && passed[x][y+1] != true)){
		a.push_back(2);
	}
	if(( x-1 >= 0 && passed[x-1][y] != true)){
		a.push_back(3);
	}
	if(( x+1 <= w-1 && passed[x+1][y] != true)){
		a.push_back(4);
	}
	//std::random_shuffle(a.begin(), a.end());
	return a;
}