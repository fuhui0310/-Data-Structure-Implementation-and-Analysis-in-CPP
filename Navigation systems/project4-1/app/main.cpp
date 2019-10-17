// main.cpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"
#include <cmath>

struct Vertex{
	int vertexNum;
	std::string name;
	RoadSegment info;
};

std::string printTime(double time){
	std::string result;
	if(time >= 3600){
		int h = time / 3600;
		int m = std::fmod(time, 3600) / 60;
		double s = std::fmod(time, 60);
		result = std::to_string(h) + " hours " + std::to_string(m) + " minutes " + std::to_string(s)+ " seconds";
	}else{
		if(time >= 60){
			int m = std::fmod(time, 3600) / 60;
			double s = std::fmod(time, 60);
			result = std::to_string(m) + " minutes " + std::to_string(s) + " seconds";
		}else{
			result = std::to_string(time) + " seconds";
		}
	}
	return result;
}


int main()
{
	std::function<double(const RoadSegment&)> shortestpath = [](RoadSegment rs){return rs.miles;};
	std::function<double(const RoadSegment&)> shortesttime = [](RoadSegment rs){return rs.miles/rs.milesPerHour;};
    RoadMapReader mapReader;
    InputReader input = InputReader(std::cin);
    RoadMap rmap = mapReader.readRoadMap(input);
    TripReader treader;
    std::vector<Trip> trips = treader.readTrips(input);
    std::map<int,int> imetric;
    for(Trip &i : trips){
    	std::vector<Vertex> vertices;
    	if(i.metric == TripMetric::Distance){
    		imetric = rmap.findShortestPaths(i.startVertex, shortestpath);
    		int evertex = i.endVertex;
        	std::string ename = rmap.vertexInfo(evertex);
        	RoadSegment einfo = rmap.edgeInfo(imetric[evertex], evertex);
        	Vertex destination = Vertex{evertex, ename, einfo};
        	vertices.push_back(destination);
        	while(evertex != i.startVertex){
        		int tmp = evertex;
        		evertex = imetric[evertex];
        		ename = rmap.vertexInfo(evertex);
        		einfo = rmap.edgeInfo(evertex, tmp);
        		Vertex current = Vertex{evertex, ename, einfo};
        		vertices.push_back(current);
        	}
        	std::cout << "Shortest distance from " << rmap.vertexInfo(vertices.back().vertexNum) << " to " << rmap.vertexInfo(vertices.front().vertexNum) << std::endl;
        	std::cout << "    Begin at " << rmap.vertexInfo(vertices.back().vertexNum) << std::endl;
    		int s = vertices.size();
    		double totalDistance = 0;
    		for(int j = 0; j < s - 1; j++){
    			Vertex tmp = vertices.back();
    			double tmpMiles = tmp.info.miles;
    			totalDistance += tmpMiles;
    			vertices.pop_back();
    			std::cout << "    Continue to " << vertices.back().name << " (" << tmpMiles << " miles)" << std::endl;
    		}
    		std::cout << "Total distance: " << totalDistance << " miles" << "\n" << std::endl;

    	}else{
    		imetric = rmap.findShortestPaths(i.startVertex, shortesttime);
    		int evertex = i.endVertex;
        	std::string ename = rmap.vertexInfo(evertex);
        	RoadSegment einfo = rmap.edgeInfo(imetric[evertex], evertex);
        	Vertex destination = Vertex{evertex, ename, einfo};
        	vertices.push_back(destination);
        	while(evertex != i.startVertex){
        		int tmp = evertex;
        		evertex = imetric[evertex];
        		ename = rmap.vertexInfo(evertex);
        		einfo = rmap.edgeInfo(evertex, tmp);
        		Vertex current = Vertex{evertex, ename, einfo};
        		vertices.push_back(current);
        	}
        	std::cout << "Shortest driving time from " << rmap.vertexInfo(vertices.back().vertexNum) << " to " << rmap.vertexInfo(vertices.front().vertexNum) << std::endl;
        	std::cout << "    Begin at " << rmap.vertexInfo(vertices.back().vertexNum) << std::endl;
    		int s = vertices.size();
    		double totalTime = 0;
    		for(int j = 0; j < s - 1; j++){
    			Vertex tmp = vertices.back();
    			double tmpMiles = tmp.info.miles;
    			double tmpMPH = tmp.info.milesPerHour;
    			double tmpTime = (tmpMiles)/(tmpMPH) * 3600;
    			totalTime += tmpTime;
    			vertices.pop_back();
    			std::cout << "    Continue to " << vertices.back().name << " (" << tmpMiles << " miles & " << tmpMPH << "mph = " << printTime(tmpTime) << ")" << std::endl;
    		}
    		std::cout << "Total time: " << printTime(totalTime) << "\n" << std::endl;
    	}
    }
    return 0;
}

