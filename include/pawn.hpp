#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece {
    public:
    Pawn(Position& location, std::string& color);
    bool canMove(const Position& from, const Position &to, const Board& board);
    void move(Position& origin, Position& destination, Piece& piece) override;
};

#endif // PAWN_HPP