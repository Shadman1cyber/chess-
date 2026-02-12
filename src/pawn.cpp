#include "pawn.hpp"

Pawn::Pawn(bool is_white, std::string name) : Piece(is_white, name) {}
bool Pawn::canMove(const Board& board, std::string destination) const{}