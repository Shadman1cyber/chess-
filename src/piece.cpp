#include "piece.hpp"

Piece::Piece(bool is_white):Is_white(is_white){}
Piece::~Piece(){}

void Piece::setColor(const bool is_white){this->Is_white = is_white;}
bool Piece::getColor() const{return Is_white;}

