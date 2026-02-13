#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Player{
    private:
        std::string name;
        int score;
    public:
        Player() = default;  
        void setName(std::string);
        std::string getName();
        void setScore(int);
        int getScore();
};

#endif // PLAYER_HPP