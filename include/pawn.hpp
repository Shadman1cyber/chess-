#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece {
    public:
    Pawn(bool is_white);
    bool canMove(const Board& board) override;
};

#endif // PAWN_HPP