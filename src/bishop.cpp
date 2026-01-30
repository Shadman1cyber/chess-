#include "bishop.hpp"

Bishop::Bishop(const std::string &color,const std::string &location) : Piece(location ,color) {}
bool Bishop::canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board){}
void Bishop::move(std::string& origin, std::string& destination, Piece& piece) {}