#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece {
    public:
        Knight(std::string location, std::string color);
        bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board);
        void move(std::string& origin, std::string& destination, Piece& piece) override;
};

#endif