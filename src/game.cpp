#include "game.hpp"
#include "king.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "piece.hpp"


Game::Game(){}
Game::Game(Player p1, Player p2, Mode) : player1(p1), player2(p2), mode(mode) {
    init();
}
Game::~Game(){}

void Game::init() {
    // Initialize the game
    // definine the pieces
    
    // Set up the board
    
    // Set up the players
    // Set up the mode
    // Set up the game loop
    // Set up the game over conditions
    // Set up the game win conditions
    // Set up the game draw conditions
    // Set up the game quit conditions
    // Set up the game pause conditions
}