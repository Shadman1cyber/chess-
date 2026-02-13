	#ifndef ARMORED_QUEEN_HPP
	#define ARMORED_QUEEN_HPP

	#include "queen.hpp"

	// وزیر زره‌دار: behaves like a Queen for movement, but the first capture
	// attempt against it is blocked by its armor. The armor is then removed,
	// and a second successful capture will remove the piece.
	class ArmoredQueen : public Queen {
	public:
	    ArmoredQueen(bool is_white, std::string name);

	    bool onCaptureAttempt(Board& board,
	                          const std::string& from,
	                          const std::string& to) override;

	private:
	    bool armor_intact = true;
	};

	#endif // ARMORED_QUEEN_HPP

