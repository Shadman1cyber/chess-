#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"
#include "board.hpp"

class Pawn : public Piece {
    public:
    Pawn(bool is_white, std::string name);
    bool canMove(const Board& board, std::string destination) const override;
};

#endif // PAWN_HPP