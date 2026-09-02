#include <iostream>
#include <ostream>
#include <string>
// #include <cstring>

#include "source/battery_set_functions.h"

using namespace std;

int main(int argc, char* argv[]) {
    // get each parameter
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
        check_words(argv[1], "-cs", true)
    ) {
        if (show_settings() == false) {
            cout << "\nSomething went wrong showing user settings..." << endl;
        }
    }

    // load settings from file
    if (
        check_words(argv[1], "--load-settings") or
        check_words(argv[1], "-ls")
    ) {
        if (load_settings(argc, argv) == false) {
            cout << "\nSomething went wrong loading user custom settings from file..." << endl;
        }
    }

    // save settings as preset on file
    if (
        check_words(argv[1], "--save-settings-preset") or
        check_words(argv[1], "-sp")
    ) {
        save_settings_preset();
    }

    // use default settings
    if (
        check_words(argv[1], "--default") or
        check_words(argv[1], "-d")
    ) {
        set_default_settings();
    }

    // show all paths in use
    if (
        check_words(argv[1], "--show-paths") or
        check_words(argv[1], "-SP")
    ) {
        show_paths();
    }

    return 0;
}
