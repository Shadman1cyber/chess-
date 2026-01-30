#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

class King : public Piece {
    public:
        King(Position& location, std::string& color);
        bool canMove(const Position& from, const Position& to, const Board& board);
        void move(Position& origin, Position& destination, Piece& piece) override;
};

#endif // KING_HPP