#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"

class Queen : public Piece {
        
    public:
        Queen(bool is_white);
        bool canMove(const Board& board) override;
};

#endif // QUEEN_HPP