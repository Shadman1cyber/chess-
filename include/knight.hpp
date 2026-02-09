#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece {
    public:
        Knight(bool is_white);
        bool canMove(const Board& board);
};

#endif