#include "queen.hpp"

Queen::Queen(Position& location, std::string& color): Piece(location, color) {}
bool Queen::canMove(const Position& from, const Position& to, const Board& board) {}
void Queen::move(Position& origin, Position& destination, Piece& piece) {}