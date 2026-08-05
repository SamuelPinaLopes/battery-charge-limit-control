#include <iostream>
#include <string>
#include <cstring>

#include "source/functions.h"

using namespace std;

bool check_words(char* word_passed, string expected, bool single=false) { // when you're passing a group of characters, make sure that you'll pass it as *, kinda array of characters    

    int index = 0;

    while (true) {
        // check each character
        if (strlen(word_passed) == expected.length() and word_passed[index] == expected[index]) {
            cout << "character: " << word_passed << " word passed" << endl << "character: " << expected[index] << " expected";
    
        }
        
        if (word_passed[index] == '\0') {
            return false;
        }

        // incrementing characters position
        index++;

    }

    return true;
}

int main(int argc, char* argv[]) {

    // variables
    int index_array_parameter = 0;

    // get each word/parameter
    while (argv[index_array_parameter] != NULL) {
        // compare each character
        if (check_words(argv[index_array_parameter], "--help") == true or check_words(argv[index_array_parameter], "-h", true) == true) { // if you put one parameters one, you'll have to put in all
            // shows the help
            cout << "help thing of battery charge limit program..." << endl;
        }

        // incrementing argv index
        index_array_parameter++;

    }

    
    




    // for (int indexarray = 0; indexarray < argc; indexarray++) {
    //     // word to check
    //     char check[] = "--help";
    //     // first char inside array slot
    //     int indexchar = 0;
    //     //     array slot index|index of char value
    //     while (argv[indexarray][indexchar] != '\0') {
    //         cout << "index: " << indexchar << "  character: " << argv[indexarray][indexchar] << endl;
    //         // incrementing 
    //         indexchar++;

    //     }

    //     cout << "\n\n" << endl;
    
    // }
    
    return 0;
}