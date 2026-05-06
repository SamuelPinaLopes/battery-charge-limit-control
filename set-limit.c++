#include <iostream>
#include "source/workdirectory.h"

using namespace std;

int main() {

    if (is_set()) {
        // set the battery limit
        std::cout << " is already setup! " << std::endl;
    } else {
        // set the configurations
        setup();
    
    }

    return 0;
}