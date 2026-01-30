#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
#include <iostream>
#include <vector>

class Bishop : public Piece {
public:
    Bishop(const std::string &color,const Position& location);
    bool canMove(const Position& from, const Position& to, const Board& board) override;
    void move(Position& origin, Position& destination, Piece& piece) override;
};

#endif // BISHOP_HPP