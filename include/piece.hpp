#ifndef PEACE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>

typedef std::pair<char, char> Position;
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
        virtual bool canMove(const std::string &from, const std::string &to, const std::vector<std::string> &board) = 0;
        virtual void move(std::string& origin, std::string& destination, Piece& piece) = 0;
};

#endif //PEACE_HPP