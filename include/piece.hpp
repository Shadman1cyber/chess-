#ifndef PEACE_HPP
#define PIECE_HPP

#include <iostream>

class Piece{
    private:
        std::string color;
        std::string Location;
        std::string Name;

    public:
        Piece(const std::string& Location, const std::string& color);
        ~Piece();
        std::string get_Location() const;
        std::string getColor() const;
        std::string getName() const;
        void set_Location(const std::string& loctaion);
        void setColor(const std::string& color);
        virtual void draw() = 0;
        virtual void move(std::string& origin, std::string& destination, Piece& piece) = 0;
    
};

#endif //PEACE_HPP