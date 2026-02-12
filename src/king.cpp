#include "king.hpp"

King::King(bool is_white,std::string name): Piece(is_white, name){}
bool King::canMove(const Board& board, std::string destination) const {}