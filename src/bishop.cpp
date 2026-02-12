#include "bishop.hpp"

Bishop::Bishop(bool is_white, std::string name) : Piece(is_white, name) {}
bool Bishop::canMove(const Board& board, std::string destination) const {}