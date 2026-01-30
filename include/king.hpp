#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

class King : public Piece {
    public:
        King(std::string location, std::string color);
        bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board);
        void move(std::string& origin, std::string& destination, Piece& piece) override;
};

#endif // KING_HPP