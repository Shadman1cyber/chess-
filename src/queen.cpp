#include "queen.hpp"

Queen::Queen(std::string location, std::string color): Piece(location, color) {}
bool Queen::canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board) {}
void Queen::move(std::string& origin, std::string& destination, Piece& piece) {}