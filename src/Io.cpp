#include "Io.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// ANSI COLORS
#define RESET "\033[0m"
#define WHITE_TEXT "\033[97m"
#define BLACK_TEXT "\033[30m"
#define GREEN_TEXT "\033[92m"

#define BG_WHITE "\033[47m"
#define BG_BLACK "\033[100m"

void IO::displayBoard(const Board& board, const vector<string>& highlights, const string& player1, const string& player2, bool white_turn)
{
    cout << "\n";
    cout << WHITE_TEXT << player2 << RESET << "\n\n";

    for (char row = '8'; row >= '1'; row--) {

        cout << " " << row << "  ";

        for (char col = 'A'; col <= 'H'; col++) {

            string pos;
            pos += col;
            pos += row;

            bool highlight = isHighlighted(pos, highlights);

            bool is_white_square =
                ((col - 'A') + (row - '1')) % 2 == 0;

            printCell(board, pos, highlight, is_white_square);
        }

        cout << RESET << "\n";
    }

    cout << "\n     A  B  C  D  E  F  G  H\n\n";

    cout << WHITE_TEXT << player1 << RESET << "\n";

    cout << "\nTurn: " << (white_turn ? "White" : "Black") << "\n\n";
}

void IO::printCell(const Board& board,const string& pos,bool highlight,bool is_white_square) const
{
    Piece* p = board.get_piece(pos);

    string bg = is_white_square ? BG_WHITE : BG_BLACK;
    cout << bg;

    if (highlight) {
        cout << GREEN_TEXT << " ● " << RESET;
        return;
    }

    if (p) {
        if (p->getColor())
            cout << WHITE_TEXT;
        else
            cout << BLACK_TEXT;

        cout << " " << p->symbol()[0] << " ";
    } else {
        cout << "   ";
    }

    cout << RESET;
}

bool IO::isHighlighted(const string& pos, const vector<string>& highlights) const
{
    return find(highlights.begin(), highlights.end(), pos)!= highlights.end();
}

void IO::printMessage(const string& msg)
{
    cout << GREEN_TEXT << msg << RESET << "\n";
}
