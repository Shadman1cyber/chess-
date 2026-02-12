#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece {
    public:
        Rook(bool is_white, std::string name);
        bool canMove(const Board& board, std::string destination) const override;
};

#endif // ROOK_HPP