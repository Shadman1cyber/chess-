#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"
#include "board.hpp"

class King : public Piece {
    public:
        King(bool is_white, std::string name);
        bool canMove(const Board& board, std::string destination) const override;
};

#endif // KING_HPP