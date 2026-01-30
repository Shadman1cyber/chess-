#include "king.hpp"

King::King(Position& location, std::string& color): Piece(location, color) {}
bool King::canMove(const Position& from, const Position& to, const Board& board) {}
void King::move(Position& origin, Position& destination, Piece& piece) {}