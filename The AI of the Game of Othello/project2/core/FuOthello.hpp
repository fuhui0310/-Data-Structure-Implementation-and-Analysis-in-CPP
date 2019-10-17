#ifndef FUOTHELLO_HPP
#define FUOTHELLO_HPP
#include "OthelloAI.hpp"
#include <vector>
#include <iostream>

namespace fhui2{

	class FuOthello : public OthelloAI{
	public:
		virtual std::pair<int,int> chooseMove(const OthelloGameState& state);
		std::vector<std::pair<int,int>> vaildMoveList(OthelloGameState& s);
		int numVaildMove(OthelloGameState& s);
		int evaluateMove(OthelloGameState& s, std::string myTiles);
		int search(OthelloGameState& s, int depth, std::string myTiles);
	};
}
#endif