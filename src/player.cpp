#include "player.hpp"

void Player::setName(std::string name){this->name = name;}
void Player::setScore(int score){this->score = score;}
std::string Player::getName(){return this->name;}
int Player::getScore(){return this->score;}