#ifndef PEACE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include "board.hpp"

typedef std::pair<char, char> Position;
class Piece{
    private:
        bool Is_white;
        std::string name; // adding a name to the piece
    public:
        Piece(bool is_white, std::string name);
        ~Piece();
        bool getColor() const;
        void setColor(bool Is_white);
        virtual bool canMove(const Board& board, std::string destination) const;
        // adding a function that returns the symbol of the piece 
        // for example pawn most return wpn idk?!
        virtual std::string symbol() const;
        // we also need a == operator
        bool operator==(const Piece &o) const;
};

#endif //PEACE_HPP