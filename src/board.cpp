#include "board.hpp"
#include "include/piece.hpp"


#include <iostream>
#include <stdexcept>


Board::Board() {}

// Copy constructor
Board::Board(const Board &board) {
    *this = board;
}

// Assignment Operator
Board& Board::operator=(const Board &board) {
    if (this == &board)
        return *this;

    cleanup();

    for (const_iterator cit = board.cbegin(); cit != board.cend(); ++cit) {
        string pos = cit.current_pos();
        Piece* piece = board(pos);

        if (piece != nullptr) {
            add_piece(pos, piece);
        }
    }

    return *this;
}


Piece* Board::operator()(const string &position) const {
    auto it = occ.find(position);
    if (it == occ.end())
        return nullptr;
    return it->second;
}


string Board::find_by_piece(const char &piece_designator) const {
    for (const auto &entry : occ) {
        if (entry.second->symbol() == piece_designator)
            return entry.first;
    }
    return "";
}


// Adds new piece to game board
void Board::add_piece(const string &position,Piece* piece) {
    if (position.size() != 2 ||
        position[0] < 'A' || position[0] > 'H' ||
        position[1] < '1' || position[1] > '8') {
        throw ("invalid position");
    }

    if (occ.find(position) != occ.end()) {
        throw ("position is occupied");
    }

    if (piece == nullptr) {
        throw ("invalid designator");
    }

    occ[position] = piece;
}

