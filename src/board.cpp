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
// Accepts coordinates in either upper- or lowercase and validates they are on the board.
void Board::add_piece(const string &position,Piece* piece) {
    if (position.size() != 2) {
        throw ("invalid position");
    }

    char file = position[0];
    char rank = position[1];

    // Normalise case only for validation (we keep the original string as the key)
    if (file >= 'a' && file <= 'h') {
        file = static_cast<char>(file - 'a' + 'A');
    }

    if (file < 'A' || file > 'H' || rank < '1' || rank > '8') {
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

        // Basic sanity check on coordinate sizes
        if (start.size() != 2 || destination.size() != 2) {
            throw ("invalid position");
        }

        char s_file = start[0];
        char s_rank = start[1];
        char d_file = destination[0];
        char d_rank = destination[1];

        // Normalise files to uppercase for validation only
        if (s_file >= 'a' && s_file <= 'h') {
            s_file = static_cast<char>(s_file - 'a' + 'A');
        }
        if (d_file >= 'a' && d_file <= 'h') {
            d_file = static_cast<char>(d_file - 'a' + 'A');
        }

        // Throw if player tries to make an illegal move (off-board coordinates)
        if (s_file < 'A' || s_file > 'H' || s_rank < '1' || s_rank > '8') {
            throw ("start position is not on board");
        }

        if (d_file < 'A' || d_file > 'H' || d_rank < '1' || d_rank > '8') {
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

