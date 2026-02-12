#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"

class Queen : public Piece {
        
    public:
        Queen(bool is_white, std::string name);
        bool canMove(const Board& board, std::string destination) const override;
};

#endif // QUEEN_HPP