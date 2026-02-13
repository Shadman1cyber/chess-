#ifndef PIECE_HPP
#define PIECE_HPP

	#include <iostream>
	#include <vector>

	class Board;
	class Piece{
    private:
        bool Is_white;
        std::string name; // adding a name to the piece
    public:
	        Piece(bool is_white, std::string name);
	        virtual ~Piece();
	        bool getColor() const;
	        void setColor(bool Is_white);
	        std::string get_name(){return name;}
	        virtual bool canMove(const Board& board, std::string destination) const;
	        // Return the unique symbol / identifier of the piece.
	        virtual std::string symbol() const;
	        // Hook called when this piece is being captured on a destination square.
	        // Return true if capture should proceed, false if it should be cancelled
	        // (used by special pieces like the Armored Queen).
	        virtual bool onCaptureAttempt(Board& board,
	                                      const std::string& from,
	                                      const std::string& to);
	        // we also need a == operator
	        bool operator==(const Piece &o) const;
};

#endif //PEACE_HPP