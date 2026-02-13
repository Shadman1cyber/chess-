#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
#include "board.hpp"
#include <iostream>
#include <vector>

class Bishop : public Piece {
public:
    Bishop(bool is_white,std::string name);
    bool canMove(const Board& board, std::string destination) const override;
};

#endif // BISHOP_HPP