/*
 * Boggle Solver
 * boggle.cpp
 *
 * Nathan Allen
 *
 */
#include "Dict.h"
#include "Board.h"
#include <fstream>

void find_words(Board *board, Dict *dictionary, int index);
void check_around(Board *board, Dict *dictionary, int index,
                  char *word, bool *passed, int length, Dict::Node *node);

int main(int argc, char *argv[])
{
        if (argc < 3) {
                cerr << "Must provide board and dictionary" << endl;
                return 0;
        }
        ifstream provided_board(argv[1]);
        Board board(provided_board);
        ifstream dict(argv[2]);
        Dict dictionary(dict);
        for (int i = 0; i < 16; ++i)
        {
               find_words(&board, &dictionary, i);
        }
        return 0;
}

/*
 * find_words
 * find all words on board starting from index
 * Arguments:
 *           pointer to Boggle Board, pointer to dictionary, starting index
 */
void find_words(Board *board, Dict *dictionary, int index)
{
        char word[16];
        for (int i = 0; i < 16; ++i) {
                word[i] = 0;
        }
        bool passed[16];
        for (int i = 0; i < 16; ++i) {
                passed[i] = false;
        }

        Dict::Node *root = dictionary->get_root();
        check_around(board, dictionary, index,
                     word, passed, 0, root);
}

/*
 * check_around
 * check current position for word, then recursively check all surrounding
 * positions
 * Arguments:
 *           pointer to Boggle Board, pointer to dictionary, current index,
 *           char array representing currently formed subword, bool array
 *           representing the passed state of each index, current length of
 *           subword, pointer to current node in dictionary
 */
void check_around(Board *board, Dict *dictionary, int index,
                  char *word, bool *passed, int length, Dict::Node *node)
{
        //ensure index is viable
        if (index < 0 || index >= 15) {
                return;
        }

        //ensure no tile is used twice in one word
        if (passed[index]) {
                return;
        }

        char tile = (*board)[index];

        //make sure we don't go down paths that can't contain words
        if (node == NULL || node->descendents[tile - 97] == NULL) {
                return;
        }
        node = node->descendents[tile - 97];
        //add char to word
        word[length] = tile;

        passed[index] = true;

        //print word if it is in dictionary
        if (dictionary->hasWord(word) && length >= 3) {
                cout << word << endl;
        }

        /* This section checks the eight adjacent directions and checks if they
           are represented on the board, and recurses on them if they are */

        unsigned row = index / 4;
        unsigned col = index % 4;

        /* Checks and runs on adjacent tiles a row above */
        //checks that the tile is not in the top row
        if (row != 0) {

                //check up
                check_around(board, dictionary,
                             index - 4, word, passed, length + 1, node);

                //checks that the tile is not in the leftmost column
                if (col != 0) {
                        //check up and left
                        check_around(board, dictionary,
                                     index - 5, word, passed, length + 1, node);
                }

                //checks that the tile is in the rightmost column
                if (col != 3) {
                        //check up and right
                        check_around(board, dictionary,
                                     index - 3, word, passed, length + 1, node);
                }
        }

        /* Checks and runs on adjacent tiles in same row */
        //checks that the tile is not in the leftmost column
        if (col != 0) {
                //check left
                check_around(board, dictionary,
                             index - 1, word, passed, length + 1, node);
        }

        //checks that the tile is not in the rightmost column
        if (col != 3) {
                //check right
                check_around(board, dictionary,
                             index + 1, word, passed, length + 1, node);
        }

        /* Checks and runs on adjacent tiles a row below */
        //checks that the tile is not in the bottom row
        if (row != 3) {
                //check down
                check_around(board, dictionary,
                             index + 4, word, passed, length + 1, node);

                //checks that the tile is not in the leftmost column
                if (col != 0) {
                        //check down and left
                        check_around(board, dictionary,
                                     index + 3, word, passed, length + 1, node);
                }

                //checks that the tile is in the rightmost column
                if (col != 3) {
                        //check down and right
                        check_around(board, dictionary,
                                     index + 5, word, passed, length + 1, node);
                }
        }

        passed[index] = false;
        word[length] = 0;
}
