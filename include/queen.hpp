#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"

class Queen : public Piece {
        Queen(Position& location, std::string& color);
        bool canMove(const Position& from, const Position& to, const Board& board);
        void move(Position& origin, Position& destination, Piece& piece) override;
};

#endif // QUEEN_HPP