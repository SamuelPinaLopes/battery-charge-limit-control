#include <iostream>
#include <string>
#include <cstring>

#include "source/functions.h"
#include "source/battery_set_functions.h"

using namespace std;

int main(int argc, char* argv[]) {
    // variables
    int index_array_parameter = 1;

    // get each word/parameter
    while (argv[index_array_parameter] != NULL) {
        // compare each character
        if (    check_words(argv[index_array_parameter], "--help")      == true 
            or  check_words(argv[index_array_parameter], "-h", true)    == true) { // if you put one parameters one, you'll have to put in all
            // shows the help
            cout << "yes it worked :O" << endl;
        } else {
            cout << "something is wrong my gentleman :|";
        }

        // incrementing argv index
        index_array_parameter++;

    }

    return 0;
}