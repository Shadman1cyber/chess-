#ifndef PEACE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include "board.hpp"

typedef std::pair<char, char> Position;
class Piece{
    private:
        std::string color;
        Position Location;
        std::string Name;

    public:
        Piece(const Position& Location, const std::string& color);
        ~Piece();
        Position get_Location() const;
        std::string getColor() const;
        std::string getName() const;
        void set_Location(const Position& loctaion);
        void setColor(const std::string& color);
        virtual bool canMove(const Position& from, const Position& to, const Board& board) = 0;
        virtual void move(Position& origin, Position& destination, Piece& piece) = 0;
};

#endif //PEACE_HPP