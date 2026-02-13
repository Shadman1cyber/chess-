	#include "game.hpp"
	#include "king.hpp"
	#include "rook.hpp"
	#include "bishop.hpp"
	#include "knight.hpp"
	#include "pawn.hpp"
	#include "queen.hpp"
	#include "piece.hpp"
	#include "super_pawn.hpp"
	#include "armored_queen.hpp"
	#include "spy.hpp"
	#include "joker_pawn.hpp"
	#include "Io.hpp"
	#include <limits>
	#include <fstream>
	#include <sstream>


	Game::Game() {
	    init();
	}
	Game::~Game(){}

	bool Game::turn = true; 

	void Game::init() {
	    // Set up the board with standard positions (using canonical coordinates A-H,1-8)
	    board.remove_all();

	    board.add_piece("A1", new Rook(true,"rw1"));
	    board.add_piece("B1", new Knight(true,"knw1"));
	    board.add_piece("C1", new Bishop(true,"bw1"));
	    // White Armored Queen instead of normal Queen
	    board.add_piece("D1", new ArmoredQueen(true,"aqw"));
	    board.add_piece("E1", new King(true,"kw"));
	    board.add_piece("F1", new Bishop(true,"bw2"));
	    board.add_piece("G1", new Knight(true,"knw2"));
	    board.add_piece("H1", new Rook(true,"rw2"));

	    // White Joker pawn and SuperPawn among the pawns
	    board.add_piece("A2", new JokerPawn(true,"jpw"));
	    board.add_piece("B2", new Pawn(true,"bpw"));
	    board.add_piece("C2", new SuperPawn(true,"spw"));
	    board.add_piece("D2", new Pawn(true,"dpw"));
	    board.add_piece("E2", new Pawn(true,"epw"));
	    board.add_piece("F2", new Pawn(true,"fpw"));
	    board.add_piece("G2", new Pawn(true,"gpw"));
	    board.add_piece("H2", new Pawn(true,"hpw"));

	    board.add_piece("A8", new Rook(false,"rb1"));
	    board.add_piece("B8", new Knight(false,"knb1"));
	    board.add_piece("C8", new Bishop(false,"bb1"));
	    board.add_piece("D8", new Queen(false,"qb"));
	    board.add_piece("E8", new King(false,"kb"));
	    board.add_piece("F8", new Bishop(false,"bb2"));
	    board.add_piece("G8", new Knight(false,"knb2"));
	    board.add_piece("H8", new Rook(false,"rb2"));

	    // One of black pawns is the Spy (hidden special piece for now)
	    board.add_piece("A7", new Spy(false,"spy1"));
	    board.add_piece("B7", new Pawn(false,"bpb"));
	    board.add_piece("C7", new Pawn(false,"cpb"));
	    board.add_piece("D7", new Pawn(false,"dpb"));
	    board.add_piece("E7", new Pawn(false,"epb"));
	    board.add_piece("F7", new Pawn(false,"fpb"));
	    board.add_piece("G7", new Pawn(false,"gpb"));
	    board.add_piece("H7", new Pawn(false,"hpb"));

	    // Set up the game meta
	    player1.setScore(0);
	    player2.setScore(0);

	    std::cout<<"Enter first player's name: ";
	    std::getline(std::cin, player1_name_buffer);
	    if (player1_name_buffer.empty()) {
	        std::getline(std::cin, player1_name_buffer);
	    }
	    player1.setName(player1_name_buffer);

	    std::cout<<"Enter second player's name: ";
	    std::getline(std::cin, player2_name_buffer);
	    if (player2_name_buffer.empty()) {
	        std::getline(std::cin, player2_name_buffer);
	    }
	    player2.setName(player2_name_buffer);

	    std::cout << "Select game mode:\n1. Standard\n2. Energy mode\n3. Mission mode\n> ";
	    int tmp = 1;
	    if (!(std::cin >> tmp)) {
	        tmp = 1;
	        std::cin.clear();
	    }
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	    if(tmp == 1){
	        mode = Mode::Standard;
	    }else if(tmp == 2){
	        mode = Mode::EnergyMode;
	    }else if(tmp == 3){
	        mode = Mode::MissionMode;
	    } else {
	        mode = Mode::Standard;
	    }

	    // Initialize history with starting position
	    history_states.clear();
	    pushHistory();
	}

	void Game::play() {
	    switch (mode) {
	        case Mode::Standard:
	            playStandard();
	            break;
	        case Mode::EnergyMode:
	            playEnergy();
	            break;
	        case Mode::MissionMode:
	            playMission();
	            break;
	        default:
	            playStandard();
	            break;
	    }
	}

	void Game::playStandard() {
	    IO io;
	    turn = true; // true = white/player1, false = black/player2

	    std::cout << "Game started (Standard mode)." << std::endl;

	    while (true) {
	        bool white_turn = turn;

	        if (!is_valid_game()) {
	            std::cout << "Invalid game state (kings missing). Ending game.\n";
	            break;
	        }

	        if (in_mate(white_turn)) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << (white_turn ? "White" : "Black") << " is checkmated. "
	                      << (!white_turn ? "White" : "Black") << " wins!\n";
	            break;
	        }

	        if (in_stalemate(white_turn)) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << "Stalemate. Draw game.\n";
	            break;
	        }

	        io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);

	        std::string from, to;
	        std::cout << (white_turn ? "White" : "Black") << " to move.\n";
	        std::cout << "Enter move as FROM TO (e.g., E2 E4), 'hint FROM', 'undo', 'save F', 'load F', or 'q' to quit: ";
	        std::cin >> from;
	        if (!std::cin) {
	            break;
	        }
	        if (from == "q" || from == "Q") {
	            std::cout << "Game aborted by user.\n";
	            break;
	        }
	        if (from == "undo" || from == "UNDO") {
	            if (!undoLast()) {
	                io.printMessage("Nothing to undo.");
	            } else {
	                io.printMessage("Reverted to previous position.");
	            }
	            continue;
	        }
	        if (from == "hint" || from == "HINT") {
	            std::string sq;
	            std::cin >> sq;
	            if (sq.size() == 2) {
	                sq[0] = static_cast<char>(std::toupper(sq[0]));
	                std::vector<std::string> moves = board.getLegalMoves(sq);
	                io.displayBoard(board, moves, player1.getName(), player2.getName(), turn);
	                std::cout << "Legal moves from " << sq << ": ";
	                for (const auto& m : moves) {
	                    std::cout << m << " ";
	                }
	                std::cout << "\n";
	            } else {
	                io.printMessage("Invalid square for hint.");
	            }
	            continue;
	        }
	        if (from == "save" || from == "SAVE") {
	            std::string filename;
	            std::cin >> filename;
	            if (!saveGame(filename)) {
	                io.printMessage("Failed to save game.");
	            } else {
	                io.printMessage("Game saved.");
	            }
	            continue;
	        }
	        if (from == "load" || from == "LOAD") {
	            std::string filename;
	            std::cin >> filename;
	            if (!loadGame(filename)) {
	                io.printMessage("Failed to load game.");
	            } else {
	                io.printMessage("Game loaded.");
	            }
	            continue;
	        }
	        std::cin >> to;
	        if (!std::cin) {
	            break;
	        }

	        if (from.size() != 2 || to.size() != 2) {
	            io.printMessage("Invalid input format. Use coordinates like E2 E4.");
	            continue;
	        }

	        // Normalise input to canonical case
	        from[0] = static_cast<char>(std::toupper(from[0]));
	        to[0]   = static_cast<char>(std::toupper(to[0]));

	        Piece* piece = board.get_piece(from);
	        if (!piece) {
	            io.printMessage("No piece on the selected source square.");
	            continue;
	        }

	        if (piece->getColor() != white_turn) {
	            io.printMessage("You must move your own piece.");
	            continue;
	        }

	        if (!piece->canMove(board, to)) {
	            io.printMessage("Illegal move for that piece.");
	            continue;
	        }

	        if (!is_path_clear(*piece, to)) {
	            io.printMessage("Path is blocked.");
	            continue;
	        }

	        if (board.wouldBeInCheckAfterMove(from, to, white_turn)) {
	            io.printMessage("This move leaves your king in check.");
	            continue;
	        }

	        // Snapshot before making a move so we can undo it later
	        pushHistory();

	        try {
	            // Perform the move (board::make_move uses piece symbol)
	            board.make_move(*piece, to);
	        } catch (const char* msg) {
	            io.printMessage(msg);
	            continue;
	        }

	        if (in_check(!white_turn)) {
	            io.printMessage("Check!");
	        }

	        // Toggle turn
	        turn = !turn;
	    }
	}

	int Game::energyCostForPiece(const Piece& p) const {
	    // Simple energy cost model based on material value
	    if (dynamic_cast<const Queen*>(&p)) return 9;
	    if (dynamic_cast<const Rook*>(&p)) return 5;
	    if (dynamic_cast<const Bishop*>(&p)) return 3;
	    if (dynamic_cast<const Knight*>(&p)) return 3;
	    if (dynamic_cast<const Pawn*>(&p)) return 1;
	    // King and other specials default to 1
	    return 1;
	}

	void Game::playEnergy() {
	    IO io;
	    turn = true;
	    white_energy = 100;
	    black_energy = 100;

	    std::cout << "Game started (Energy mode)." << std::endl;

	    while (true) {
	        bool white_turn = turn;
	        int& current_energy = white_turn ? white_energy : black_energy;
	        int& opponent_energy = white_turn ? black_energy : white_energy;

	        if (!is_valid_game()) {
	            std::cout << "Invalid game state (kings missing). Ending game.\n";
	            break;
	        }

	        if (current_energy <= 0) {
	            std::cout << (white_turn ? "White" : "Black")
	                      << " has no energy left and loses.\n";
	            break;
	        }

	        if (in_mate(white_turn)) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << (white_turn ? "White" : "Black") << " is checkmated. "
	                      << (!white_turn ? "White" : "Black") << " wins!\n";
	            break;
	        }

	        if (in_stalemate(white_turn)) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << "Stalemate. Draw game.\n";
	            break;
	        }

	        io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	        std::cout << "Energy - White: " << white_energy
	                  << " | Black: " << black_energy << "\n";

	        std::string from, to;
	        std::cout << (white_turn ? "White" : "Black") << " to move.\n";
	        std::cout << "Enter move as FROM TO (e.g., E2 E4), 'hint FROM', 'undo', 'save F', 'load F', or 'q' to quit: ";
	        std::cin >> from;
	        if (!std::cin) {
	            break;
	        }
	        if (from == "q" || from == "Q") {
	            std::cout << "Game aborted by user.\n";
	            break;
	        }
	        if (from == "undo" || from == "UNDO") {
	            if (!undoLast()) {
	                io.printMessage("Nothing to undo.");
	            } else {
	                io.printMessage("Reverted to previous position.");
	            }
	            continue;
	        }
	        if (from == "hint" || from == "HINT") {
	            std::string sq;
	            std::cin >> sq;
	            if (sq.size() == 2) {
	                sq[0] = static_cast<char>(std::toupper(sq[0]));
	                std::vector<std::string> moves = board.getLegalMoves(sq);
	                io.displayBoard(board, moves, player1.getName(), player2.getName(), turn);
	                std::cout << "Legal moves from " << sq << ": ";
	                for (const auto& m : moves) {
	                    std::cout << m << " ";
	                }
	                std::cout << "\n";
	            } else {
	                io.printMessage("Invalid square for hint.");
	            }
	            continue;
	        }
	        if (from == "save" || from == "SAVE") {
	            std::string filename;
	            std::cin >> filename;
	            if (!saveGame(filename)) {
	                io.printMessage("Failed to save game.");
	            } else {
	                io.printMessage("Game saved.");
	            }
	            continue;
	        }
	        if (from == "load" || from == "LOAD") {
	            std::string filename;
	            std::cin >> filename;
	            if (!loadGame(filename)) {
	                io.printMessage("Failed to load game.");
	            } else {
	                io.printMessage("Game loaded.");
	            }
	            continue;
	        }
	        std::cin >> to;
	        if (!std::cin) {
	            break;
	        }

	        if (from.size() != 2 || to.size() != 2) {
	            io.printMessage("Invalid input format. Use coordinates like E2 E4.");
	            continue;
	        }

	        from[0] = static_cast<char>(std::toupper(from[0]));
	        to[0]   = static_cast<char>(std::toupper(to[0]));

	        Piece* piece = board.get_piece(from);
	        if (!piece) {
	            io.printMessage("No piece on the selected source square.");
	            continue;
	        }

	        if (piece->getColor() != white_turn) {
	            io.printMessage("You must move your own piece.");
	            continue;
	        }

	        int cost = energyCostForPiece(*piece);

	        if (!piece->canMove(board, to)) {
	            io.printMessage("Illegal move for that piece.");
	            continue;
	        }

	        if (!is_path_clear(*piece, to)) {
	            io.printMessage("Path is blocked.");
	            continue;
	        }

	        if (board.wouldBeInCheckAfterMove(from, to, white_turn)) {
	            io.printMessage("This move leaves your king in check.");
	            continue;
	        }

	        Piece* target = board.get_piece(to);
	        bool is_capture = (target && target->getColor() != white_turn);
	        int refund = is_capture ? energyCostForPiece(*target) : 0;

	        if (current_energy - cost < 0) {
	            io.printMessage("Not enough energy for that move.");
	            continue;
	        }

	        // Snapshot before making a move for undo
	        pushHistory();

	        try {
	            board.make_move(*piece, to);
	        } catch (const char* msg) {
	            io.printMessage(msg);
	            continue;
	        }

	        current_energy -= cost;
	        if (is_capture) {
	            current_energy += refund;
	        }

	        if (in_check(!white_turn)) {
	            io.printMessage("Check!");
	        }

	        turn = !turn;
	    }
	}

	void Game::playMission() {
	    IO io;
	    turn = true;

	    // Simple mission: White must capture the black queen within 10 white moves.
	    mission_for_white = true;
	    mission_max_turns = 10;
	    mission_turns_used = 0;
	    mission_description = "Mission: White must capture the black queen within 10 white moves.";

	    std::cout << "Game started (Mission mode)." << std::endl;
	    std::cout << mission_description << "\n";

	    while (true) {
	        bool white_turn = turn;

	        if (!is_valid_game()) {
	            std::cout << "Invalid game state (kings missing). Ending game.\n";
	            break;
	        }

	        // Check mission success: black queen gone
	        if (board.find_by_piece("qb").empty()) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << "Mission accomplished! Black queen has been captured.\n";
	            break;
	        }

	        // Check mission failure: out of moves for mission player
	        if (mission_for_white && mission_turns_used >= mission_max_turns) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << "Mission failed: White did not capture the black queen in time.\n";
	            break;
	        }

	        if (in_mate(white_turn)) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << (white_turn ? "White" : "Black") << " is checkmated. "
	                      << (!white_turn ? "White" : "Black") << " wins!\n";
	            break;
	        }

	        if (in_stalemate(white_turn)) {
	            io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	            std::cout << "Stalemate. Draw game.\n";
	            break;
	        }

	        io.displayBoard(board, {}, player1.getName(), player2.getName(), white_turn);
	        if (mission_for_white) {
	            std::cout << "Mission moves used (White): " << mission_turns_used
	                      << "/" << mission_max_turns << "\n";
	        }

	        std::string from, to;
	        std::cout << (white_turn ? "White" : "Black") << " to move.\n";
	        std::cout << "Enter move as FROM TO (e.g., E2 E4), 'hint FROM', 'undo', 'save F', 'load F', or 'q' to quit: ";
	        std::cin >> from;
	        if (!std::cin) {
            break;
	        }
	        if (from == "q" || from == "Q") {
	            std::cout << "Game aborted by user.\n";
	            break;
	        }
	        if (from == "undo" || from == "UNDO") {
	            if (!undoLast()) {
	                io.printMessage("Nothing to undo.");
	            } else {
	                io.printMessage("Reverted to previous position.");
	            }
	            continue;
	        }
	        if (from == "hint" || from == "HINT") {
	            std::string sq;
	            std::cin >> sq;
	            if (sq.size() == 2) {
	                sq[0] = static_cast<char>(std::toupper(sq[0]));
	                std::vector<std::string> moves = board.getLegalMoves(sq);
	                io.displayBoard(board, moves, player1.getName(), player2.getName(), turn);
	                std::cout << "Legal moves from " << sq << ": ";
	                for (const auto& m : moves) {
	                    std::cout << m << " ";
	                }
	                std::cout << "\n";
	            } else {
	                io.printMessage("Invalid square for hint.");
	            }
	            continue;
	        }
	        if (from == "save" || from == "SAVE") {
	            std::string filename;
	            std::cin >> filename;
	            if (!saveGame(filename)) {
	                io.printMessage("Failed to save game.");
	            } else {
	                io.printMessage("Game saved.");
	            }
	            continue;
	        }
	        if (from == "load" || from == "LOAD") {
	            std::string filename;
	            std::cin >> filename;
	            if (!loadGame(filename)) {
	                io.printMessage("Failed to load game.");
	            } else {
	                io.printMessage("Game loaded.");
	            }
	            continue;
	        }
	        std::cin >> to;
	        if (!std::cin) {
	            break;
	        }

	        if (from.size() != 2 || to.size() != 2) {
	            io.printMessage("Invalid input format. Use coordinates like E2 E4.");
	            continue;
	        }

	        from[0] = static_cast<char>(std::toupper(from[0]));
	        to[0]   = static_cast<char>(std::toupper(to[0]));

	        Piece* piece = board.get_piece(from);
	        if (!piece) {
	            io.printMessage("No piece on the selected source square.");
	            continue;
	        }

	        if (piece->getColor() != white_turn) {
	            io.printMessage("You must move your own piece.");
	            continue;
	        }

	        if (!piece->canMove(board, to)) {
	            io.printMessage("Illegal move for that piece.");
	            continue;
	        }

	        if (!is_path_clear(*piece, to)) {
	            io.printMessage("Path is blocked.");
	            continue;
	        }

	        if (board.wouldBeInCheckAfterMove(from, to, white_turn)) {
	            io.printMessage("This move leaves your king in check.");
	            continue;
	        }

	        // Snapshot before making a move
	        pushHistory();

	        try {
	            board.make_move(*piece, to);
	        } catch (const char* msg) {
	            io.printMessage(msg);
	            continue;
	        }

	        if (mission_for_white && white_turn) {
	            ++mission_turns_used;
	        }

	        if (in_check(!white_turn)) {
	            io.printMessage("Check!");
	        }

	        turn = !turn;
	    }
	}

	bool Game::saveGame(const std::string& filename) const {
	    std::ofstream out(filename);
	    if (!out.is_open()) {
	        return false;
	    }
	    out << serializeState();
	    return true;
	}

	bool Game::loadGame(const std::string& filename) {
	    std::ifstream in(filename);
	    if (!in.is_open()) {
	        return false;
	    }

	    std::stringstream buffer;
	    buffer << in.rdbuf();
	    return deserializeState(buffer.str());
	}

	std::string Game::serializeState() const {
	    std::ostringstream out;
	    out << "CHESSPP_V1\n";
	    out << "MODE " << static_cast<int>(mode) << "\n";
	    out << "TURN " << (turn ? "W" : "B") << "\n";
	    out << "PLAYER1 " << player1.getName() << "\n";
	    out << "PLAYER2 " << player2.getName() << "\n";
	    out << "ENERGY " << white_energy << " " << black_energy << "\n";
	    out << "MISSION " << mission_for_white << " " << mission_max_turns
	        << " " << mission_turns_used << "\n";

	    // Pieces
	    for (char col = 'A'; col <= 'H'; ++col) {
	        for (char row = '1'; row <= '8'; ++row) {
	            std::string pos;
	            pos += col;
	            pos += row;
	            Piece* p = board.get_piece(pos);
	            if (!p) continue;

	            std::string type = "PIECE";
	            if (dynamic_cast<King*>(p)) type = "KING";
	            else if (dynamic_cast<ArmoredQueen*>(p)) type = "ARMORED_QUEEN";
	            else if (dynamic_cast<Queen*>(p)) type = "QUEEN";
	            else if (dynamic_cast<Rook*>(p)) type = "ROOK";
	            else if (dynamic_cast<Bishop*>(p)) type = "BISHOP";
	            else if (dynamic_cast<Knight*>(p)) type = "KNIGHT";
	            else if (dynamic_cast<SuperPawn*>(p)) type = "SUPER_PAWN";
	            else if (dynamic_cast<JokerPawn*>(p)) type = "JOKER_PAWN";
	            else if (dynamic_cast<Spy*>(p)) type = "SPY";
	            else if (dynamic_cast<Pawn*>(p)) type = "PAWN";

	            out << "PIECE " << type << " "
	                << (p->getColor() ? "W" : "B") << " "
	                << p->symbol() << " "
	                << pos << "\n";
	        }
	    }

	    return out.str();
	}

	bool Game::deserializeState(const std::string& data) {
	    std::istringstream in(data);

	    std::string header;
	    std::getline(in, header);
	    if (header != "CHESSPP_V1") {
	        return false;
	    }

	    // Reset board and some state
	    board.remove_all();

	    std::string line;
	    while (std::getline(in, line)) {
	        if (line.empty()) continue;
	        std::istringstream iss(line);
	        std::string tag;
	        iss >> tag;
	        if (tag == "MODE") {
	            int m; iss >> m;
	            if (m == 0) mode = Mode::Standard;
	            else if (m == 1) mode = Mode::EnergyMode;
	            else if (m == 2) mode = Mode::MissionMode;
	            else mode = Mode::Standard;
	        } else if (tag == "TURN") {
	            char t; iss >> t;
	            turn = (t == 'W');
	        } else if (tag == "PLAYER1") {
	            std::string name;
	            std::getline(iss >> std::ws, name);
	            player1.setName(name);
	        } else if (tag == "PLAYER2") {
	            std::string name;
	            std::getline(iss >> std::ws, name);
	            player2.setName(name);
	        } else if (tag == "ENERGY") {
	            iss >> white_energy >> black_energy;
	        } else if (tag == "MISSION") {
	            int mf;
	            iss >> mf >> mission_max_turns >> mission_turns_used;
	            mission_for_white = (mf != 0);
	        } else if (tag == "PIECE") {
	            std::string type, color_str, name, pos;
	            iss >> type >> color_str >> name >> pos;
	            bool is_white = (color_str == "W");

	            Piece* p = nullptr;
	            if (type == "KING") p = new King(is_white, name);
	            else if (type == "ARMORED_QUEEN") p = new ArmoredQueen(is_white, name);
	            else if (type == "QUEEN") p = new Queen(is_white, name);
	            else if (type == "ROOK") p = new Rook(is_white, name);
	            else if (type == "BISHOP") p = new Bishop(is_white, name);
	            else if (type == "KNIGHT") p = new Knight(is_white, name);
	            else if (type == "SUPER_PAWN") p = new SuperPawn(is_white, name);
	            else if (type == "JOKER_PAWN") p = new JokerPawn(is_white, name);
	            else if (type == "SPY") p = new Spy(is_white, name);
	            else if (type == "PAWN") p = new Pawn(is_white, name);

	            if (p) {
	                board.add_piece(pos, p);
	            }
	        }
	    }

	    return true;
	}

	void Game::pushHistory() {
	    // Limit history to avoid unbounded memory growth
	    if (history_states.size() > 100) {
	        history_states.erase(history_states.begin());
	    }
	    history_states.push_back(serializeState());
	}

	bool Game::undoLast() {
	    if (history_states.size() < 2) {
	        return false;
	    }
	    // Remove current state
	    history_states.pop_back();
	    // Restore previous
	    const std::string& prev = history_states.back();
	    return deserializeState(prev);
	}


// added by me(ali)

bool Game::is_path_linear(const string& start, const string& end) const {

    int dc = end[0] - start[0];
    int dr = end[1] - start[1];

    if (dc == 0 || dr == 0)
        return true;

    if (abs(dc) == abs(dr))
        return true;

    return false;
}

bool Game::is_path_clear(const Piece p, const string& destination) const {

    string start = board.find_by_piece(p.symbol());

    if (!is_path_linear(start, destination))
        return true; // knights ignore

    int dc = (destination[0] - start[0]);
    int dr = (destination[1] - start[1]);

    dc = (dc == 0) ? 0 : dc / abs(dc);
    dr = (dr == 0) ? 0 : dr / abs(dr);

    char col = start[0] + dc;
    char row = start[1] + dr;

    while (col != destination[0] || row != destination[1]) {
        string pos;
        pos += col;
        pos += row;

        if (board.get_piece(pos) != nullptr)
            return false;

        col += dc;
        row += dr;
    }

    return true;
}

bool Game::in_check(const bool& white) const {
    return board.isInCheck(white);
}

bool Game::in_mate(const bool& white) const {
    return board.isCheckmate(white);
}

bool Game::in_stalemate(const bool& white) const {
    return board.isStalemate(white);
}


int Game::point_value(const bool& white) const {

    int score = 0;

    for (char col = 'A'; col <= 'H'; col++) {
        for (char row = '1'; row <= '8'; row++) {

            string pos;
            pos += col;
            pos += row;

            Piece* p = board.get_piece(pos);

            if (!p || p->getColor() != white)
                continue;

            if (dynamic_cast<Queen*>(p)) score += 9;
            else if (dynamic_cast<Rook*>(p)) score += 5;
            else if (dynamic_cast<Bishop*>(p)) score += 3;
            else if (dynamic_cast<Knight*>(p)) score += 3;
            else if (dynamic_cast<Pawn*>(p)) score += 1;
        }
    }

    return score;
}
