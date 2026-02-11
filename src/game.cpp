#include "game.hpp"
#include "king.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "piece.hpp"


Game::Game(Player& p1, Player& p2, Mode) : player1(p1), player2(p2), mode(mode) {
    init();
}
Game::~Game(){}

void Game::init() {
    // Initialize the game
    // definine the pieces
    King kw(true), kb(false);
    Rook rw1(true), rb1(false), rw2(true), rb2(false);
    Bishop bw1(true), bb1(false), bw2(true), bb2(false);
    Knight knw1(true), knb1(false), knw2(true), knb2(false);
    Queen qw(true), qb(false);
    Pawn apw(true), apb(false), bpw(true), bpb(false), cpw(true), cpb(false), dpw(true), dpb(false), epw(true), epb(false), fpw(true), fpb(false), gpw(true), gpb(false), hpw(true), hpb(false);
    // Set up the board
    Board board;
    // Set up the pieces
    board.add_piece("a1",&rw1);
    board.add_piece("b1",&knw1);
    board.add_piece("c1",&bw1);
    board.add_piece("d1",&qw);
    board.add_piece("e1",&kw);
    board.add_piece("f1",&bw2);
    board.add_piece("g1",&knw2);
    board.add_piece("h1",&rw2);
    board.add_piece("a2",&apw);
    board.add_piece("b2",&bpw);
    board.add_piece("c2",&cpw);
    board.add_piece("d2",&dpw);
    board.add_piece("e2",&epw);
    board.add_piece("f2",&fpw);
    board.add_piece("g2",&gpw);
    board.add_piece("h2",&hpw);
    board.add_piece("a7",&apb);
    board.add_piece("b7",&bpb);
    board.add_piece("c7",&cpb);
    board.add_piece("d7",&dpb);
    board.add_piece("e7",&epb);
    board.add_piece("f7",&fpb);
    board.add_piece("g7",&gpb);
    board.add_piece("h7",&hpb);
    board.add_piece("a8",&rb1);
    board.add_piece("b8",&knb1);
    board.add_piece("c8",&bb1);
    board.add_piece("d8",&qb);
    board.add_piece("e8",&kb);
    board.add_piece("f8",&bb2);
    board.add_piece("g8",&knb2);
    board.add_piece("h8",&rb2);
    // Set up the game
    player1.setScore(0);
    player2.setScore(0);
    std::cout<<"enter first players name:";
    std::string name;
    cin >> name;
    player1.setName(name);
    std::cout<<"enter second players name:";
    cin >> name;
    player2.setName(name);
    play();
}

void Game::play() {
    std::cout << "Game started" << std::endl;
    // Game loop
    while (true) {
        if(turn){
            std::string tmp;
            std::cout << "Player 1's turn" << std::endl;
            std::cout << "chose your piece:" << std::endl;
            cin >> tmp;
        }
        else{
            std::cout << "Player 2's turn" << std::endl;
        }
    }
}