This is a Boggle solver; that is, it takes in a Boggle board and a dictionary
and it finds all words on the board, as per the rules of Boggle.

It can be compiled with the line 

		clang++ -o boggle boggle.cpp Board.cpp Dict.cpp

 in a Unix command line. This will create an executable
called "boggle", which can be run like so:

        ./boggle <board> <dictionary>
        
with \<board\> and \<dictionary\> as two .txt files.

This project has been implemented up until Step 3 in the implementation plan in
DESIGN.
