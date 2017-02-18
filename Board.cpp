/*
 * Board.cpp
 * Implementation of Board.h
 *
 * Nathan Allen
 *
 */

#include "Board.h"
#include <assert.h>
#include <stdio.h>

Board::Board()
{
        board = new char[16];
}

Board::Board(string s)
{
        assert(s.length() >= 16);
        board = new char[16];
        for (int i = 0; i < 16; i++) {
                board[i] = s[i];
        }
}

Board::Board(istream &input)
{
        string s = "";
        input >> s;
        board = new char[16];
        for (int i = 0; i < 16; i++) {
                board[i] = s[i];
        }
}

Board::~Board()
{
        delete[] board;
}