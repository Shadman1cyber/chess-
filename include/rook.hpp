#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece {
    public:
        Rook(std::string location, std::string color);
        bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board);
        void move(std::string& origin, std::string& destination, Piece& piece) override;

};

#endif // ROOK_HPP