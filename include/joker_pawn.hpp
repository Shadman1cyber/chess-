	#ifndef JOKER_PAWN_HPP
	#define JOKER_PAWN_HPP

	#include "pawn.hpp"

	// جوکر: currently behaves like a normal pawn; in later phases we can extend it
	// to mimic other pieces' movement temporarily. The separate type keeps the design
	// ready for that extension.
	class JokerPawn : public Pawn {
	public:
	    JokerPawn(bool is_white, std::string name);

	    // For now, same movement as Pawn – override reserved for future behaviour.
	};

	#endif // JOKER_PAWN_HPP

