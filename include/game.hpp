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
        int turn;
        Player winner;
        
    public:
        Game();
        Game(Player, Player, Mode);
        ~Game();
        void init();
        void play();
        void printBoard();
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
};

#endif //GAME_HPP