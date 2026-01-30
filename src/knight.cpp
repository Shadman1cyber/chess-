#include "knight.hpp"

Knight::Knight(Position& location, std::string& color): Piece(location, color) {}
bool Knight::canMove(const Position& from, const Position& to, const Board& board) {}
void Knight::move(Position& origin, Position& destination, Piece& piece) {}