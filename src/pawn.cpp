#include "pawn.hpp"

Pawn::Pawn(std::string location, std::string color) : Piece(location, color) {}
bool Pawn::canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board){}
void Pawn::move(std::string& origin, std::string& destination, Piece& piece){}