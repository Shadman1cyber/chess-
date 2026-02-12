#include "knight.hpp"

Knight::Knight(bool is_white, std::string name): Piece(is_white, name) {}
bool Knight::canMove(const Board& board, std::string destination) const{}