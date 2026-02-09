#ifndef PEACE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include "board.hpp"

typedef std::pair<char, char> Position;
class Piece{
    private:
        bool Is_white;

    public:
        Piece(bool is_white);
        ~Piece();
        bool getColor() const;
        void setColor(bool Is_white);
        virtual bool canMove(const Board& board) = 0;
};

#endif //PEACE_HPP