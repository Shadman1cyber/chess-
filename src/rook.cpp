#include "rook.hpp"

Rook::Rook(bool is_white,std::string name) : Piece(is_white,name) {}
bool Rook::canMove(const Board& board, std::string destination) const{}