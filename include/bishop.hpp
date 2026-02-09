#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
#include <iostream>
#include <vector>

class Bishop : public Piece {
public:
    Bishop(bool is_white);
    bool canMove(const Board& board) override;
};

#endif // BISHOP_HPP