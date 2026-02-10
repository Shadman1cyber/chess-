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
        virtual bool canMove(const Board& board);
        // adding a function that returns the symbol of the piece 
        // for example pawn most return wpn idk?!
        virtual char symbol() const;
        // we also need a == operator
        bool operator==(const Piece &o) const;
};

#endif //PEACE_HPP