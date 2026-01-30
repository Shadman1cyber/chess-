#include "bishop.hpp"

Bishop::Bishop(const std::string& color,const Position& location) : Piece(location ,color) {}
bool Bishop::canMove(const Position& from, const Position& to, const Board& board){}
void Bishop::move(Position& origin, Position& destination, Piece& piece) {}