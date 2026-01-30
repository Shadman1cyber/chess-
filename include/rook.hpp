#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece {
    public:
        Rook(Position& location, std::string& color);
        bool canMove(const Position& from, const Position& to, const Board& board);
        void move(Position& origin, Position& destination, Piece& piece) override;
};

#endif // ROOK_HPP