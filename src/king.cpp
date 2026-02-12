#include "king.hpp"

King::King(bool is_white,std::string name): Piece(is_white, name){}
bool King::canMove(const Board& board, std::string destination) const {

    std::string from = board.findKing(this->getColor());
    int dc = std::abs(from[0] - destination[0]);
    int dr = std::abs(from[1] - destination[1]);

    if (dc > 1 || dr > 1 || (dc == 0 && dr == 0))
        return false;

    Piece* dest = board.return_piece(destination);
    if (dest && dest->getColor() == this->getColor())
        return false;

    if (board.isSquareUnderAttack(destination, !this->getColor()))
        return false;

    return true;
}
