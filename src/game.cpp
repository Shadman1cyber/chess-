#include "game.hpp"
#include "king.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "piece.hpp"


Game::Game() {
    init();
}
Game::~Game(){}

void Game::init() {
    // Initialize the game
    // definine the pieces
    King kw(true,"kw"), kb(false,"kb");
    Rook rw1(true,"rw1"), rb1(false,"rb1"), rw2(true,"rw2"), rb2(false,"rb2");
    Bishop bw1(true,"bw1"), bb1(false,"bb1"), bw2(true,"bw2"), bb2(false,"bb2");
    Knight knw1(true,"knw1"), knb1(false,"knb1"), knw2(true, "knw2"), knb2(false,"knb2");
    Queen qw(true, "qw"), qb(false,"qb");
    Pawn apw(true,"apw"), apb(false,"apb"), bpw(true,"bpw"), bpb(false,"bpb"), cpw(true,"cpw"), cpb(false,"cpb"), dpw(true,"dpw"), dpb(false,"dpb"), epw(true,"epw"), epb(false,"epb"), fpw(true,"fpw"), fpb(false,"fpb"), gpw(true,"gpw"), gpb(false,"gpb"), hpw(true,"hpw"), hpb(false,"hpb");
    // Set up the board
    static Board board;
    // Set up the pieces

    board.add_piece("a1", new Rook(true,"rw1"));
    board.add_piece("b1", new Knight(true,"knw1"));
    board.add_piece("c1", new Bishop(true,"bw1"));
    board.add_piece("d1", new Queen(true,"qw"));
    board.add_piece("e1", new King(true,"kw"));
    board.add_piece("f1", new Bishop(true,"bw2"));
    board.add_piece("g1", new Knight(true,"knw2"));
    board.add_piece("h1", new Rook(true,"rw2"));

    board.add_piece("a2", new Pawn(true,"apw"));
    board.add_piece("b2", new Pawn(true,"bpw"));
    board.add_piece("c2", new Pawn(true,"cpw"));
    board.add_piece("d2", new Pawn(true,"dpw"));
    board.add_piece("e2", new Pawn(true,"epw"));
    board.add_piece("f2", new Pawn(true,"fpw"));
    board.add_piece("g2", new Pawn(true,"gpw"));
    board.add_piece("h2", new Pawn(true,"hpw"));

    board.add_piece("a8", new Rook(false,"rb1"));
    board.add_piece("b8", new Knight(false,"knb1"));
    board.add_piece("c8", new Bishop(false,"bb1"));
    board.add_piece("d8", new Queen(false,"qb"));
    board.add_piece("e8", new King(false,"kb"));
    board.add_piece("f8", new Bishop(false,"bb2"));
    board.add_piece("g8", new Knight(false,"knb2"));
    board.add_piece("h8", new Rook(false,"rb2"));

    board.add_piece("a7", new Pawn(false,"apb"));
    board.add_piece("b7", new Pawn(false,"bpb"));
    board.add_piece("c7", new Pawn(false,"cpb"));
    board.add_piece("d7", new Pawn(false,"dpb"));
    board.add_piece("e7", new Pawn(false,"epb"));
    board.add_piece("f7", new Pawn(false,"fpb"));
    board.add_piece("g7", new Pawn(false,"gpb"));
    board.add_piece("h7", new Pawn(false,"hpb"));

    // Set up the game
    player1.setScore(0);
    player2.setScore(0);
    std::cout<<"enter first players name:\n";
    std::string name;
    cin >> name;
    player1.setName(name);
    std::cout<<"enter second players name:\n";
    cin >> name;
    player2.setName(name);
    std::cout << "enter your game mode:\n 1.standard\n2.energy mode\n3.mission mode\n";
    int tmp = 0;
    cin >> tmp;
    if(tmp == 1){
        mode = Mode::Standard;
    }else if(tmp == 2){
        mode = Mode::EnergyMode;
    }else if(tmp == 3){
        mode = Mode::MissionMode;
    }
    play(board);
}

void Game::play(Board& board) {
    std::cout << "Game started" << std::endl;
    // Game loop
    turn = true;
    while (true && mode == Mode::Standard) {
        while(turn){
            std::string stmp;
            std::cout << "Player 1's turn" << std::endl;
            std::cout << "chose your piece:" << std::endl;
            cin >> stmp;
            if(stmp == "" && board.find_by_piece(stmp) != ""){
                Piece ptmp = *board.return_piece(stmp);
                std::cout << "chose your destination: \n";
                cin >> stmp;
                if(ptmp.canMove(board,stmp) && is_path_clear(ptmp,stmp)){
                    make_move(ptmp,stmp);
                }
            }else if(board.find_by_piece(stmp) == ""){
                std::cout << "There's no such piece" << std::endl;
            }else if(stmp == ""){
                std::cout << "You need to chose a piece" << std::endl;
            }
        }
        while (!turn){
            std::string stmp;
            std::cout << "Player 2's turn" << std::endl;
            std::cout << "chose your piece:" << std::endl;
            cin >> stmp;
            if(stmp == "" && board.find_by_piece(stmp) != ""){
                Piece ptmp = *board.return_piece(stmp);
                std::cout << "chose your destination: \n";
                cin >> stmp;
                if(ptmp.canMove(board,stmp) && is_path_clear(ptmp,stmp)){
                    make_move(ptmp,stmp);
                }
            }else if(stmp == ""){
                std::cout << "You need to chose a piece" << std::endl;
            }else if(board.find_by_piece(stmp) == ""){
                std::cout << "There's no such piece" << std::endl;
            }
        }
    }
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
