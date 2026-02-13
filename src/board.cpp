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
// Accepts coordinates in either upper- or lowercase and stores them in canonical form (A-H,1-8).
void Board::add_piece(const string &position,Piece* piece) {
    if (position.size() != 2) {
        throw ("invalid position");
    }

    char file = position[0];
    char rank = position[1];

    // Normalise file to uppercase for both validation and storage
    if (file >= 'a' && file <= 'h') {
        file = static_cast<char>(file - 'a' + 'A');
    }

    if (file < 'A' || file > 'H' || rank < '1' || rank > '8') {
        throw ("invalid position");
    }

    std::string key;
    key += file;
    key += rank;

    if (occ.find(key) != occ.end()) {
        throw ("position is occupied");
    }

    if (piece == nullptr) {
        throw ("invalid designator");
    }

    occ[key] = piece;
}

bool Board::isSquareUnderAttack(const std::string& square, bool by_white) const {
    for (char col = 'A'; col <= 'H'; col++) {
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
    for (char col = 'A'; col <= 'H'; col++) {
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
    // Simulate the move on the current board without allocating a copy.
    // Note: this function is logically const, but we temporarily modify and restore state.
    Board* self = const_cast<Board*>(this);

    Piece* moving = self->return_piece(from);
    if (!moving) return true;

    Piece* captured = self->return_piece(to);

    self->setPiece(to, moving);
    self->setPiece(from, nullptr);

    bool in_check = self->isInCheck(is_white);

    // Restore original state
    self->setPiece(from, moving);
    self->setPiece(to, captured);

    return in_check;
}


std::vector<std::string> Board::getLegalMoves(const std::string& from) const {
    std::vector<std::string> legal;
    Piece* p = return_piece(from);
    if (!p) return legal;

    bool is_white = p->getColor();

    for (char col = 'A'; col <= 'H'; col++) {
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

        // Normalise files to uppercase for validation and storage
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

        std::string start_key, dest_key;
        start_key += s_file;
        start_key += s_rank;
        dest_key += d_file;
        dest_key += d_rank;

        // Handle potential capture on destination
        auto it = occ.find(dest_key);
        if (it != occ.end() && it->second) {
            Piece* target = it->second;
            // Ask the target whether the capture should proceed
            if (!target->onCaptureAttempt(*this, start_key, dest_key)) {
                throw ("capture prevented by special piece");
            }
            delete target;
            occ.erase(it);
        }

        occ.erase(start_key);
        occ[dest_key] = &p;

}


    Piece* Board::get_piece(const string& position) const {
    if (position.size() != 2) return nullptr;

    char file = position[0];
    char rank = position[1];

    if (file >= 'a' && file <= 'h') {
        file = static_cast<char>(file - 'a' + 'A');
    }

    std::string key;
    key += file;
    key += rank;

    auto it = occ.find(key);
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

void Board::remove_piece(const string& position) {
    if (position.size() != 2) return;

    char file = position[0];
    char rank = position[1];

    if (file >= 'a' && file <= 'h') {
        file = static_cast<char>(file - 'a' + 'A');
    }

    std::string key;
    key += file;
    key += rank;

    auto it = occ.find(key);
    if (it != occ.end()) {
        delete it->second;
        occ.erase(it);
    }
}

bool Board::has_valid_kings() const {
    int white_kings = 0;
    int black_kings = 0;

    for (const auto& entry : occ) {
        if (dynamic_cast<King*>(entry.second)) {
            if (entry.second->getColor())
                ++white_kings;
            else
                ++black_kings;
        }
    }

    return (white_kings == 1 && black_kings == 1);
}

void Board::display() const {
    // Simple board dump without colors; IO handles fancy UI.
    for (char row = '8'; row >= '1'; --row) {
        std::cout << row << " ";
        for (char col = 'A'; col <= 'H'; ++col) {
            std::string pos;
            pos += col;
            pos += row;
            Piece* p = nullptr;
            auto it = occ.find(pos);
            if (it != occ.end())
                p = it->second;

            if (p) {
                std::cout << p->symbol()[0] << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for (char row = '8'; row >= '1'; --row) {
        os << row << " ";
        for (char col = 'A'; col <= 'H'; ++col) {
            std::string pos;
            pos += col;
            pos += row;
            Piece* p = nullptr;
            auto it = board.occ.find(pos);
            if (it != board.occ.end())
                p = it->second;

            if (p) {
                os << p->symbol()[0] << " ";
            } else {
                os << ". ";
            }
        }
        os << std::endl;
    }
    os << "  A B C D E F G H" << std::endl;
    return os;
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

