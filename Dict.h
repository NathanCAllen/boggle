/*
 * Dict.h
 * A 26-branch trie that stores all words in the english language under 16
 * letters long
 *
 * Nathan Allen
 *
 */

#include <iostream>


using namespace std;

class Dict
{
public:
        //constructs an empty Dictionary
        Dict();

        //constructs a Dictionary and puts int all words in file
        Dict(istream &file);

        //destructor that calls deleteChildren
        ~Dict();

        struct Node {
                Node **descendents;
                bool word;
                bool leaf;
        };

        //checks if the passed string is a word
        bool hasWord(string word);

        //checks if the passed string ends at a leaf
        bool isLeaf(string word);

        //adds a word to the Dictionary
        void addWord(string word);

        Node *get_root() {return root;}

private:
	//start of trie
	Node *root;

        //pointer to the first node in the trie

        //helper function for destructor
        void deleteChildren(Node *node);

        //helper function for 
        bool isLeaf(Node *node);

        //returns char's placement in alphabet
        int num_char(char c);

        //set all members of node->descendents to NULL
        void nullify_descendents(Node **descendents);
};
