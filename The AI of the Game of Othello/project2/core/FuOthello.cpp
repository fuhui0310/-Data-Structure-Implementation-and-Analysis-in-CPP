#include "FuOthello.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, fhui2::FuOthello, "FU AI(Required)");

std::pair<int,int> fhui2::FuOthello::chooseMove(const OthelloGameState& state){
	std::pair<int, int> chosen;
	int score = 0;
	int max = -999;
	std::string myTiles;
	if(state.isBlackTurn()){
		myTiles = "Black";
	}else{
		myTiles = "White";
	}
	std::unique_ptr<OthelloGameState> s = state.clone();
	std::vector<std::pair<int, int>> v = vaildMoveList(*s);
	for(auto possibleMove: v){
		std::unique_ptr<OthelloGameState> c = state.clone();
		c->makeMove(possibleMove.first, possibleMove.second);
		score = evaluateMove(*c, myTiles);
		score += search(*c, 3, myTiles);
		if(score >= max){
			max = score;
			chosen = possibleMove;
		}
	}
	return chosen;
}

std::vector<std::pair<int,int>> fhui2::FuOthello::vaildMoveList(OthelloGameState& s){
	std::vector<std::pair<int,int>> list;
	for(int i = 0; i < s.board().width(); i++){
		for(int j = 0; j< s.board().height(); j++){
			std::pair<int,int> validCell;
			if(s.isValidMove(i,j)){
				validCell.first = i;
				validCell.second = j;
				list.push_back(validCell);
			}
		}
	}
	return list;
}

int fhui2::FuOthello::numVaildMove(OthelloGameState& s){
	int total = 0;
	for(int i = 0; i < s.board().width(); i++){
		for(int j = 0; j< s.board().height(); j++){
			if(s.isValidMove(i,j)){
				total++;
			}
		}
	}
	return total;
}

int fhui2::FuOthello::evaluateMove(OthelloGameState& s, std::string myTiles){
	int moveScore = 0;
	if(myTiles == "Black"){
		if(s.isBlackTurn()){
			moveScore= s.blackScore()-s.whiteScore();
			if(s.board().cellAt(0,0) == OthelloCell::black)
				moveScore += 15;
			if(s.board().cellAt(0,s.board().height()- 1) == OthelloCell::black)
				moveScore += 15;
			if(s.board().cellAt(s.board().width()- 1,0) == OthelloCell::black)
				moveScore += 15;
			if(s.board().cellAt(s.board().width()- 1, s.board().height()- 1) == OthelloCell::black)
				moveScore += 15;
			/*if(s.board().cellAt(1,0) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(0,1) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(1,s.board().height()- 1) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(0,s.board().height()- 2) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 2,0) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 1,1) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 1, s.board().height()- 2) == OthelloCell::black)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 2, s.board().height()- 1) == OthelloCell::black)
				moveScore -= 3;*/
			//moveScore += numVaildMove(s);
		}else{
			moveScore= s.whiteScore() - s.blackScore();
			if(s.board().cellAt(0,0) == OthelloCell::white)
				moveScore -= 10;
			if(s.board().cellAt(0,s.board().height()- 1) == OthelloCell::white)
				moveScore -= 10;
			if(s.board().cellAt(s.board().width()- 1,0) == OthelloCell::white)
				moveScore -= 10;
			if(s.board().cellAt(s.board().width()- 1, s.board().height()- 1) == OthelloCell::white)
				moveScore -= 10;
			moveScore -= numVaildMove(s);
		}
	}else{
		if(s.isWhiteTurn()){
			moveScore= s.whiteScore() - s.blackScore();
			if(s.board().cellAt(0,0) == OthelloCell::white)
				moveScore += 15;
			if(s.board().cellAt(0,s.board().height()- 1) == OthelloCell::white)
				moveScore += 15;
			if(s.board().cellAt(s.board().width()- 1,0) == OthelloCell::white)
				moveScore += 15;
			if(s.board().cellAt(s.board().width()- 1, s.board().height()- 1) == OthelloCell::white)
				moveScore += 15;
			/*if(s.board().cellAt(1,0) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(0,1) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(1,s.board().height()- 1) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(0,s.board().height()- 2) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 2,0) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 1,1) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 1, s.board().height()- 2) == OthelloCell::white)
				moveScore -= 3;
			if(s.board().cellAt(s.board().width()- 2, s.board().height()- 1) == OthelloCell::white)
				moveScore -= 3;*/
			//moveScore += numVaildMove(s);
		}else{
			moveScore= s.blackScore()-s.whiteScore();
			if(s.board().cellAt(0,0) == OthelloCell::black)
				moveScore -= 10;
			if(s.board().cellAt(0,s.board().height()- 1) == OthelloCell::black)
				moveScore -= 10;
			if(s.board().cellAt(s.board().width()- 1,0) == OthelloCell::black)
				moveScore -= 10;
			if(s.board().cellAt(s.board().width()- 1, s.board().height()- 1) == OthelloCell::black)
				moveScore -= 10;
			moveScore -= numVaildMove(s);
		}
	}
	return moveScore;
}

int fhui2::FuOthello::search(OthelloGameState& s, int depth, std::string myTiles){
	if(s.isGameOver()){
		return evaluateMove(s, myTiles);
	}
	if(depth == 0){
		return evaluateMove(s, myTiles);
	}
	int moveScore = 0;
	int max = -999;
	std::vector<std::pair<int, int>> v = vaildMoveList(s);
	for(auto possibleMove: v){
		std::unique_ptr<OthelloGameState> c = s.clone();
		c->makeMove(possibleMove.first, possibleMove.second);
		moveScore = search(*c, depth-1, myTiles);
		if(moveScore >= max){
			max = moveScore;
		}
	}
	return evaluateMove(s, myTiles) + max;
}