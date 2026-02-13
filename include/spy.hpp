	#ifndef SPY_HPP
	#define SPY_HPP

	#include "piece.hpp"

	// جاسوس بی‌پدر: for now we implement it as a special piece that moves
	// like a bishop or a rook (i.e., queen-like movement), but future phases
	// can extend its behaviour (hidden allegiance, delayed reveal, etc.).
	class Spy : public Piece {
	public:
	    Spy(bool is_white, std::string name);

	    bool canMove(const Board& board, std::string destination) const override;
	};

	#endif // SPY_HPP

