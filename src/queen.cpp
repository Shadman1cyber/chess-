#include "queen.hpp"

Queen::Queen(bool is_white, std::string name): Piece(is_white, name) {}
bool Queen::canMove(const Board& board, std::string destination) const{}