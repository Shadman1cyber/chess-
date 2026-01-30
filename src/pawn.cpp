#include "pawn.hpp"

Pawn::Pawn(Position& location, std::string& color) : Piece(location, color) {}
bool Pawn::canMove(const Position& from, const Position& to, const Board& board){}
void Pawn::move(Position& origin, Position& destination, Piece& piece){}