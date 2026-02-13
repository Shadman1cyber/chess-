	#include "joker_pawn.hpp"

	JokerPawn::JokerPawn(bool is_white, std::string name)
	    : Pawn(is_white, std::move(name)) {}

