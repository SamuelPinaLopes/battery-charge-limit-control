#include <iostream>
#include "source/functions.h"

using namespace std;

int main() {

    // check if program's folders are setup
    if (is_set()) {
        // set limit 
        write_limit();

    } else {
        // set configurations
        setup();

        // set limit
        write_limit();
    
    }

    return 0;
}