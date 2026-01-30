#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"

class Queen : public Piece {
        Queen(std::string location, std::string color);
        bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board);
        void move(std::string& origin, std::string& destination, Piece& piece) override;
};

#endif // QUEEN_HPP