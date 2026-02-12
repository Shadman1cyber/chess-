#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece {
    public:
        Knight(bool is_white, std::string name);
        bool canMove(const Board& board, std::string destination) const;
};

#endif