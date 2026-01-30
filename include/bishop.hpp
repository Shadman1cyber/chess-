#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
#include <iostream>
#include <vector>

class Bishop : public Piece {
public:
    Bishop(const std::string &color,const std::string &location);
    bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board) override;
    void move(std::string& origin, std::string& destination, Piece& piece) override;
};

#endif // BISHOP_HPP