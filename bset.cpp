#include <iostream>
#include "source/functions.h"

using namespace std;

int main(int argc, char* argv[]) {

    for (int indexarray = 0; indexarray < argc; indexarray++) {
        // word to check
        char check[] = "--help";
        // first char inside array slot
        int indexchar = 0;
        //     array slot index|index of char value
        while (argv[indexarray][indexchar] != '\0') {
            cout << "index: " << indexchar << "  character: " << argv[indexarray][indexchar] << endl;
            // incrementing
            indexchar++;

        }

        cout << "\n\n" << endl;
    
    }
    
    return 0;
}