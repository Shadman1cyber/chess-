#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece {
    public:
    Pawn(std::string location, std::string color);
    bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board);
    void move(std::string& origin, std::string& destination, Piece& piece) override;
};

#endif // PAWN_HPP