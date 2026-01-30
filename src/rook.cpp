#include "rook.hpp"

Rook::Rook(Position& location, std::string& color) : Piece(location, color) {}
bool Rook::canMove(const Position& from, const Position& to, const Board& board) {}
void Rook::move(Position& origin, Position& destination, Piece& piece) {}