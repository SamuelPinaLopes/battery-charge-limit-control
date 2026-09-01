#include <iostream>
#include <ostream>
#include <string>
#include <cstring>

#include "source/battery_set_functions.h"

using namespace std;

int main(int argc, char* argv[]) {
    // variables
    int index_array_parameter = 1;

    // get each word/parameter
    while (argv[index_array_parameter] != NULL) {
        //                        general help
        if ( // if you put one parameters name, you'll have to put for all
            check_words(argv[index_array_parameter], "--help") == true or
            check_words(argv[index_array_parameter], "-h", true) == true
        ) {
            // shows the help
            cout << "yes it worked :O\n for general help" << endl;
        }

        //                      program's settings
        // show current settings
        if (
            check_words(argv[index_array_parameter], "--show-settings") or
            check_words(argv[index_array_parameter], "-cs", true)
        ) {
            if (show_settings() == false) {
                cout << "\nSomething went wrong showing user settings..." << endl;
            }
        }

        // load settings from file
        if (
            check_words(argv[index_array_parameter], "--load-settings") or
            check_words(argv[index_array_parameter], "-ls")
        ) {
            load_settings();
        }
        // save settings as preset / on a file
        if (
            check_words(argv[index_array_parameter], "--save-preset") or
            check_words(argv[index_array_parameter], "-sp")
        ) {
            save_settings_preset();
        }
        // use default settings
        if (
            check_words(argv[index_array_parameter], "--default") or
            check_words(argv[index_array_parameter], "-d")
        ) {
            set_default_settings();
        }
        // show all paths in use
        if (
            check_words(argv[index_array_parameter], "--show-paths") or
            check_words(argv[index_array_parameter], "-SP")
        ) {
            show_paths();
        }

        // incrementing argv index
        index_array_parameter++;

    }

    return 0;
}
