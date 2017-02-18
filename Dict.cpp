/*
 * Dict.cpp
 * Implementation of Dict.h
 *
 * Nathan Allen
 *
 */

#include "Dict.h"

Dict::Dict()
{
        Node *temp = new Node();
        root = temp;
        root->leaf = true;
        root->word = false;
        root->descendents = new Node*[26];
        nullify_descendents(root->descendents);
}

Dict::Dict(istream &input)
{
        Node *temp = new Node();
        root = temp;
        root->leaf = true;
        root->word = false;
        root->descendents = new Node*[26];
        nullify_descendents(root->descendents);
        string s = "";
        while (true) { //will end internally
                input >> s;
                if (input.fail()) break;
                addWord(s);
        }
}

Dict::~Dict()
{
        if (root!=NULL) {
                deleteChildren(root);
        }
}

/*
 * hasWord
 * checks if the passed word is in the Dict
 * Arugments:
 *           string representing the word
 * Returns:
 *         boolean representing whether the word is in the Dict
 */
bool Dict::hasWord(string word)
{
        Node *it = root;
        char c;
        int letter;

        for (size_t x = 0; x < word.length(); x++) {
                c = word[x];
                letter = num_char(c);
                if (it->descendents[letter] == NULL)
                        return false;
                it = it->descendents[letter];
        }

        if (it->word)
                return true;

        return false;
}

/*
 * addWord
 * adds word to Dict
 * Arguments:
 *           string representing the word
 */
void Dict::addWord(string word)
{
        //cerr << "into addWord";
        //node pointer starting at root
        //iterates over each char of word
                //checks if there is a path to char through node
                        //makes path if none exists
                //moves node down path
        //sets node as a word
        if (word == "")
                return;
        Node *it = root;
        char c = 0;
        int letter = 0;

        for (size_t x = 0; x < word.length(); x++) {
                c = word[x];
                letter = num_char(c);
                if (it->leaf || it->descendents[letter] == NULL) {
                        it->descendents[letter] = new Node();
                        it->descendents[letter]->word = false;
			it->descendents[letter]->descendents = new Node*[26];
                        nullify_descendents(
                                        it->descendents[letter]->descendents);
                        it->descendents[letter]->leaf = true;
                }
                it->leaf = false;
                it = it->descendents[letter];
        }

        it->word = true;
}

/*
 * deleteChildren
 * helper function for destructor, post order deletes Dict
 * Arguments:
 *           node pointer to be deleted
 */
void Dict::deleteChildren(Node *node)
{
        if (node == NULL) return;
        for (int i = 0; i < 26; i++) {
                deleteChildren(node->descendents[i]);
        }
        delete[] node->descendents;
        delete node;
}

/*
 * num_char
 * returns the placement of passed char in alphabet 
 * (ex. num_char('a') returns 0)
 * Arguments:
 *           char to be decremented
 * Returns:
 *         decremented char, cast as int
 */
int Dict::num_char(char c)
{
        return (int) c - 97;
}

/*
 * nullify_descendents
 * sets the node pointers in a node's descendents array to NULL
 * Arguments:
 *           node pointer array
 */
void Dict::nullify_descendents(Node **descendents)
{
        for (int i = 0; i < 26; i++)
        {
                descendents[i] = NULL;
        }
}