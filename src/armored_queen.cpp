	#include "armored_queen.hpp"
	#include "board.hpp"

	ArmoredQueen::ArmoredQueen(bool is_white, std::string name)
	    : Queen(is_white, std::move(name)) {}

	bool ArmoredQueen::onCaptureAttempt(Board& /*board*/,
	                                    const std::string& /*from*/,
	                                    const std::string& /*to*/) {
	    if (armor_intact) {
	        armor_intact = false;
	        // First hit only removes armor; queen survives and capture is cancelled.
	        return false;
	    }
	    // Armor already gone – capture proceeds normally.
	    return true;
	}

