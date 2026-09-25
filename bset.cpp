#include <fstream>
#include <iostream>
#include <string>
#include "source/battery_set_functions.h"

using namespace std;

int main(int argc, char* argv[]) {

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

        // show all presets avaiable
        if (
            check_words(argv[1], "--show-presets") or
            check_words(argv[1], "-sp")
        ) {
            show_presets();
        }

        // select a preset/setting file to use
        if (
            check_words(argv[1], "--select-preset") or
            check_words(argv[1], "-se")
        ) {
            use_preset();
        }

    } else {
        /* apply limit through settings */
        /*
         * open config file;
         * get the name of the settings to use;
         * close config file;
         * open settings file to use;
         * get the charge limit;
         * close settings file;
         * open .runtime.conf
         * write the value from settings file;
         * close runtime file;
         * run worker program to apply that;
         */

        ifstream configuration("/etc/BatterYLimiT/config.conf");
        string line;
        string limit;

        // get each line
        while (getline(configuration, line)) {
            // check if the first character matches the size of "settings"
            if (line.substr(0, 7) == "setting") {
                // get its value
                limit = line.substr(8, line.length()-1);
                cout << "preset name: " << limit << endl;
            }
        }

        // close the file
        configuration.close();

    }

    return 0;
}
