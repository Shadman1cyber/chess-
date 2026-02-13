	#ifndef SUPER_PAWN_HPP
	#define SUPER_PAWN_HPP

	#include "pawn.hpp"

	// سرباز++ : like a normal pawn but can also capture straight ahead in addition
	// to the two diagonal capture squares.
	class SuperPawn : public Pawn {
	public:
	    SuperPawn(bool is_white, std::string name);

	    bool canMove(const Board& board, std::string destination) const override;
	};

	#endif // SUPER_PAWN_HPP

