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
        static bool turn;
        Player winner;
        // Internal buffers for reading full-line player names
        std::string player1_name_buffer;
        std::string player2_name_buffer;
        // Energy mode state
        int white_energy = 100;
        int black_energy = 100;
        // Mission mode state
        int mission_max_turns = 0;
        int mission_turns_used = 0;
        bool mission_for_white = true;
        std::string mission_description;
        // History for undo/redo-like behaviour
        std::vector<std::string> history_states;
        // Internal helpers
        void playStandard();
        void playEnergy();
        void playMission();
        int energyCostForPiece(const Piece& p) const;
        // Persistence helpers
        bool saveGame(const std::string& filename) const;
        bool loadGame(const std::string& filename);
        // In-memory serialization for history / undo
        std::string serializeState() const;
        bool deserializeState(const std::string& data);
        void pushHistory();
        bool undoLast();
        
    public:
        Game();
        ~Game();
        void init();
        void play();
        void printBoard(){board.display();}


        // these are added

        static bool turn_white() { return turn; }

        bool is_valid_game() const { return board.has_valid_kings(); }
		bool in_check(const bool& white) const;
		// Test if the path is clear to the destination
		bool is_path_clear(const Piece p, const string& destination) const;
		// Is the path linear (diagonal, horizontal, vertical)
		bool is_path_linear(const string& start, const string& end) const;
		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;
		// Returns true if the designated player is in mate
		bool in_stalemate(const bool& white) const;
    	// Returns the total material point value of the designated player
        int point_value(const bool& white) const;

};

#endif //GAME_HPP