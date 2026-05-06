#include <iostream>
#include "source/workdirectory.h"

using namespace std;

int main() {

    if (is_set()) {
        // set the battery limit
        if (write_limit()) {
            cout << "battery limit set";
        } else {
            cout << "battery limit isn't set yet";
        }

    } else {
        // set the configurations
        setup();
    
    }

    return 0;
}