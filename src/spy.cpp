	#include "spy.hpp"
	#include "board.hpp"
	#include <cmath>

	Spy::Spy(bool is_white, std::string name)
	    : Piece(is_white, std::move(name)) {}

	bool Spy::canMove(const Board& board, std::string destination) const {

	    std::string start = board.find_by_piece(symbol());
	    if (start.empty())
	        return false;

	    int dc = std::abs(destination[0] - start[0]);
	    int dr = std::abs(destination[1] - start[1]);

	    // Queen-like movement (combination of rook + bishop)
	    if (!(start[0] == destination[0] || start[1] == destination[1] || dc == dr))
	        return false;

	    Piece* target = board.get_piece(destination);
	    if (target && target->getColor() == getColor())
	        return false;

	    return true;
	}

