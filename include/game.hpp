#ifndef GAME_HPP
#define GAME_HPP

#include "mode.hpp"
#include "player.hpp"
#include "board.hpp"

class Game {
    private:
        Player player1, player2;
        Mode mode;
        Board board;
        // i changed turn type to boolian (ali)
        bool turn;
        Player winner;
        
    public:
        Game();
        Game(Player, Player, Mode);
        ~Game();
        void init();
        void play();
        // i added implementation of printBoard function here (ali)
        void printBoard(){board.display();}
        void printWinner();
        void printTurn();
        void printPlayer();
        void printMode();
        void setPlayer(Player, Player);
        void setMode(Mode);
        void setTurn(int);
        void setWinner(Player);
        Player getPlayer1();
        Player getPlayer2();
        Mode getMode();
        int getTurn();
        Player getWinner();


        // these are added by me(ali)

        Game& operator=(const Game &game);
        // Returns true if it is white's turn
        bool turn_white() const { return turn; }

        bool is_valid_game() const { return board.has_valid_kings(); }
        void make_move(const Position& start, const Position& end);
		bool in_check(const bool& white) const;
		// Test if the path is clear to the destination
		bool is_path_clear(const Position& start, const Position& end) const;
		// Is the path linear (diagonal, horizontal, vertical)
		bool is_path_linear(const Position& start, const Position& end) const;
		// Sees if a move will result in check
		bool would_check(const Position &start, const Position &end) const;
		// determines if a piece is elligible to be promoted
		bool check_promotion(const Position& start, const Position& end) const;
		// Determines if a move is legal
		bool is_possible_move(const Position& pos) const;
		// Tries to see if a player can move to allow king to escape from check
		bool prevent_check(const Position& pos) const;
		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;
		// Returns true if the designated player is in mate
		bool in_stalemate(const bool& white) const;
    	// Returns the total material point value of the designated player
        int point_value(const bool& white) const;

};

#endif //GAME_HPP