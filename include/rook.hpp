#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece {
    public:
        Rook(bool is_white);
        bool canMove(const Board& board) override;
};

#endif // ROOK_HPP