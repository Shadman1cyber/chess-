#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

class King : public Piece {
    public:
        King(bool is_white);
        bool canMove(const Board& board) override;
};

#endif // KING_HPP