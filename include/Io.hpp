#ifndef IO_HPP
#define IO_HPP
#include "board.hpp"
#include <vector>
#include <string>

class IO{
    public:
        void displayBoard(const Board& board, const std::vector<std::string>& highlights = {}, const std::string& player1 = "", const std::string& player2 = "", bool white_turn = true);

        void printMessage(const std::string& msg);

    private:
        void printCell(const Board& board, const std::string& pos, bool highlight, bool is_white_square) const;
        bool isHighlighted(const std::string& pos, const std::vector<std::string>& highlights) const;

    };

#endif 