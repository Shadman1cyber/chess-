#include "piece.hpp"

Piece::Piece(const Position& Location, const std::string& color) : Location(Location), color(color){}
Piece::~Piece(){}

void Piece::set_Location(const Position& location){
    this->Location = Location;
}
void Piece::setColor(const std::string& color){
    this->color = color;
}
std::string Piece::getColor() const{
    return color;
}
Position Piece::get_Location() const{
    return Location;
}
std::string Piece::getName()const{
    return Name;
}

