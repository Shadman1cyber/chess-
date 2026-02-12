#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <map>
#include "piece.hpp"

using namespace std;

class Board{
        // Throughout, we will be accessing board positions using Position defined in Piece.h.
        // The assumption is that the first value is the column with values in
        // {'A','B','C','D','E','F','G','H'} (all caps)
        // and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

    public:
        // Default constructor
        Board();

        // Copy constructor
        Board(const Board &b);

        // Overload assignment operator 
        Board& operator=(const Board &b);

        // Destructor
        ~Board();

        // Returns a const pointer to the piece at a prescribed location if it exists,
        // or nullptr if there is nothing there.
        Piece* operator() (const string& position) const;

        // Returns the position of the requested piece
        string find_by_piece(const string& piece_designator) const;

        //added by me (mahdi)
        Piece return_piece(std::string name) const;
        void setPiece(const std::string& destination, Piece* p);

        //check detection
        bool isSquareUnderAttack(const std::string& square, bool by_white) const;
        std::string findKing(bool is_white) const;
        bool isInCheck(bool is_white) const;

        //legal move filtering
        bool wouldBeInCheckAfterMove(const std::string& from,const std::string& to, bool is_white) const;
        std::vector<std::string> getLegalMoves(const std::string& from) const;

        bool isCheckmate(bool is_white) const;
        bool isStalemate(bool is_white) const;
        // Attempts to add a new piece with the specified designator, at the given position.
        // Throw exception for the following cases:
        // -- the designator is invalid, throw exception with error message "invalid designator"
        // -- the specified position is not on the board, throw exception with error message "invalid position"
        // -- if the specified position is occupied, throw exception with error message "position is occupied"
        void add_piece(const string& position, Piece* piece);

        Piece* get_piece(const string& position) const;

        // Removes a piece object at the given position.
        void remove_piece(const string& position);

        // Remove all pieces in a board
        void remove_all();

        // Displays the board by printing it to stdout
        void display() const;

        // Returns true if the board has the right number of kings on it
        bool has_valid_kings() const;

        // Cleanup function for removing any allocated memory
        void cleanup();

        // Map to store the locations and types of each piece
        typedef map<string, Piece*> BoardType;

        // Constant Iterator for the Board object
        // Keeps track of a cell location at all times, and moves up/right
        class const_iterator {
            public:

                const_iterator(std::string initial_pos) : pos(initial_pos) {}
                const_iterator& operator++() {
                    if (pos.empty())
                        return *this;

                    char cur_col = pos[0];
                    char cur_row = pos[1]; 

                    if (cur_col == 'H') {
                        if (cur_row == '8') {
                            pos = "";
                        } else {
                            pos = string{ 'A', char(cur_row + 1) };
                        }
                    } else {
                        pos = string{ char(cur_col + 1), cur_row };
                    }

                    return *this;
                    }

            const std::string& operator*() const {
                return pos;
            }

            // Overload == operator to check if two iterators point to the same location
            bool operator==(const const_iterator &o) const { 
                return (pos[0] == o.pos[0] && pos[1] == o.pos[1]);
            }

            // Checks if two iterators don't point to the same location
            bool operator!=(const const_iterator &o) const { return !(*this == o); }

            // Returns position the iterator is currently on
            string current_pos() { return pos; }

            private:
                string pos;
        };

       const_iterator cend() const {
            return const_iterator("");
        }

        // Returns an iterator pointing to first cell in the board (bottom-left)
        const_iterator cbegin() const {
            return const_iterator(string{"A1"});
        }

        void make_move(Piece& p, const string& destination);

    private:
        // The sparse map storing the pieces, keyed off locations
        map<string, Piece*> occ;

        // Write the board state to an output stream
        friend ostream& operator<< (ostream& os, const Board& board);
};

#endif //BOARD_HPP