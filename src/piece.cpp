#include "piece.hpp"

Piece::Piece(bool is_white, std::string name):Is_white(is_white), name(name){}
Piece::~Piece(){}

void Piece::setColor(const bool is_white){this->Is_white = is_white;}
bool Piece::getColor() const{return Is_white;}

