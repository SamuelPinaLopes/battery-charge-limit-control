#include <iostream>
#include "source/battery_set_functions.h"

using namespace std;

int main(int argc, char* argv[]) {

    // get each parameter
    if (argc > 1) {
        //                        general help
        if ( // if you put one parameters name, you'll have to put for all
            check_words(argv[1], "--help") == true or
            check_words(argv[1], "-h", true) == true
        ) {
            // shows the help
            cout << "yes it worked :O\n for general help" << endl;
        }

        //                      program's settings
        // show current settings
        if (
            check_words(argv[1], "--show-settings") or
            check_words(argv[1], "-ss", true)
        ) {
            show_settings();
        }

        // save settings as preset on file
        if (
            check_words(argv[1], "--create-preset") or
            check_words(argv[1], "-cp")
        ) {
            save_settings_preset();
        }

        // use default settings
        if (
            check_words(argv[1], "--default-settings") or
            check_words(argv[1], "-ds")
        ) {
            set_default_settings();
        }

        // set a new charge limit on current time
        if  (
            check_words(argv[1], "--set") or
            check_words(argv[1], "-s")
        ) {
            set_limit();
        }

    }

    return 0;
}
