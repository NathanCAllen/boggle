/*
 * Board.h
 * A 4x4 two-dimensional array of characters that represents a Boggle board
 *
 * Nathan Allen
 *
 */

#include <iostream>

using namespace std;

class Board
{
public:
        //constructs an empty Board
        Board();

        //constructs a Board containing passed string
        Board(string s);

        //constructs a Board containing data from argument
        Board(istream &input);

        //simple deconstructor
        ~Board();

        //bracket operator overload
        char& operator[](int index) {return board[index];}

private:
        //represents board of characters
        char *board;
};