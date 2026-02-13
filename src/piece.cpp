	#include "piece.hpp"

	Piece::Piece(bool is_white, std::string name):Is_white(is_white), name(name){}
	Piece::~Piece(){}

	void Piece::setColor(const bool is_white){this->Is_white = is_white;}
	bool Piece::getColor() const{return Is_white;}


	std::string Piece::symbol() const {
	    return name;
	}

	bool Piece::onCaptureAttempt(Board& /*board*/,
	                             const std::string& /*from*/,
	                             const std::string& /*to*/) {
	    // By default captures always succeed.
	    return true;
	}

	bool Piece::operator==(const Piece &o) const {
	    return (Is_white == o.Is_white && name == o.name);
	}

	bool Piece::canMove(const Board& /*board*/, std::string /*destination*/) const {
	    // Base piece cannot move (must override in derived classes)
	    return false;
	}
