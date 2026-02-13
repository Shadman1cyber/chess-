#include "board.hpp"
#include "king.hpp"
#include "game.hpp"

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


string Board::find_by_piece(const std::string& piece_designator) const {
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

bool Board::isSquareUnderAttack(const std::string& square, bool by_white) const {
    for (char col = 'a'; col <= 'h'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            std::string pos;
            pos += col;
            pos += row;

            Piece* p = return_piece(pos);
            if (!p || p->getColor() != by_white) 
                continue;

            if (dynamic_cast<King*>(p)) {
                int dc = std::abs(pos[0] - square[0]);
                int dr = std::abs(pos[1] - square[1]);
                if (dc <= 1 && dr <= 1 && (dc + dr > 0))
                    return true;
            } else {
                if (p->canMove(*this, square))
                    return true;
            }
        }
    }
    return false;
}

std::string Board::findKing(bool is_white) const {
    for (char col = 'a'; col <= 'h'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            std::string pos;
            pos += col;
            pos += row;

            Piece* p = return_piece(pos);
            if (p && p->getColor() == is_white && dynamic_cast<King*>(p))
                return pos;
        }
    }
    return "";
}

bool Board::isInCheck(bool is_white) const {
    std::string king_pos = findKing(is_white);
    if (king_pos.empty()) 
        return false;

    return isSquareUnderAttack(king_pos, !is_white);
}

bool Board::wouldBeInCheckAfterMove(const std::string& from, const std::string& to, bool is_white) const {
    Board temp(*this);

    Piece* moving = temp.return_piece(from);
    if (!moving) return true;

    temp.setPiece(to, moving);
    temp.setPiece(from, nullptr);

    return temp.isInCheck(is_white);
}

std::vector<std::string> Board::getLegalMoves(const std::string& from) const {
    std::vector<std::string> legal;
    Piece* p = return_piece(from);
    if (!p) return legal;

    bool is_white = p->getColor();

    for (char col = 'a'; col <= 'h'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            std::string dest;
            dest += col;
            dest += row;

            if (dest == from) 
                continue;

            if (!p->canMove(*this, dest)) 
                continue;

            if (!wouldBeInCheckAfterMove(from, dest, is_white))
                legal.push_back(dest);
        }
    }
    return legal;
}

bool Board::isCheckmate(bool is_white) const {

    if (!isInCheck(is_white)) {
        return false;
    }

    for (char col = 'A'; col <= 'H'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            std::string pos;
            pos += col;
            pos += row;

            Piece* p = (*this)(pos);
            if (p && p->getColor() == is_white) {
                std::vector<std::string> moves = getLegalMoves(pos);
                if (!moves.empty()) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Board::isStalemate(bool is_white) const {
    if (isInCheck(is_white)) {
        return false;
    }

    for (char col = 'A'; col <= 'H'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            std::string pos;
            pos += col;
            pos += row;

            Piece* p = (*this)(pos);
            if (p && p->getColor() == is_white) {
                std::vector<std::string> moves = getLegalMoves(pos);
                if (!moves.empty()) {
                    return false;
                }
            }
        }
    }

    return true;
}


void Board::make_move(Piece& p, const string& destination) {
        
        string start = find_by_piece(p.symbol());
        
        // Throw s if player tries to make an illegal move
        if (start[0] > 'H' || start[0] < 'A' || start[1] < '1' || start[1] > '8') {
            throw ("start position is not on board");
        }

        

        if (destination[0] > 'H' || destination[1] < 'A' || destination[2] < '1' || destination[2] > '8') {
            throw ("destination position is not on board");
        }

        if (p.getColor() != Game::turn_white()) {
            throw ("piece color and turn do not match");
        }
        
        occ.erase(start);
        occ[destination] = &p;

	}


    Piece* Board::get_piece(const string& position) const {
    auto it = occ.find(position);
    if (it == occ.end())
        return nullptr;
    return it->second;
    }

    void Board::cleanup() {
    for (auto &entry : occ) {
        delete entry.second;
    }
    occ.clear();
    }

    void Board::remove_all() {
    cleanup();
    }

    // Add this function to board.cpp
void Board::setPiece(const std::string& position, Piece* piece) {
    if (piece == nullptr) {
        // Remove piece at position
        auto it = occ.find(position);
        if (it != occ.end()) {
            occ.erase(it);
        }
    } else {
        // Set/replace piece at position
        occ[position] = piece;
    }
}

// Add destructor implementation
Board::~Board() {
    cleanup();
}

