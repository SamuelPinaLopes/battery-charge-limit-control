#include "utilities.h"
#include "parameters.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc > 1) {
        //                        general help
        if ( // if you put one parameters name, you'll have to put for all
            check_words(argv[1], "--help") == true or
            check_words(argv[1], "-h", true) == true
        ) {
            // shows the help
            cout<< "----battery charge limit general help----"
                << "\n\n --help  prints this message\n -h"
                << "\n\n\nchange settings"
                << "\n\n --show-settings  show program settings\n -ss"
                << "\n\n --create-preset  creates a new preset from current battery charge limit settings in use.\n -cp"
                << "\n\n --default-settings  factory reset program's settings.\n -ds"
                << "\n\n --set  change current battery charge limit. (its value will be reset after reboot or caming from hibernation.\n -s"
                << "\n\n --show-presets  shows all battery charge limit presets avaiable to use.\n -sp"
                << "\n\n --select-preset  select one battery charge limit preset to use.\n -se"
                << "\n\n --new-limit  change current settings battery charge limit value.\n -n"
                << endl;
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

        // define a battery charge limit for current settings
        if (
            check_words(argv[1], "--new-limit") or
            check_words(argv[1], "-n")
        ) {
            define_limit();
        }

    } else {
        // apply limit through settings
        /*
         * open config file; done
         * get the name of the settings to use; done
         * close config file; done
         * open settings file to use; done
         * get the charge limit; done
         * close settings file; done
         * open .runtime.conf; done
         * write the value from settings file; done
         * close runtime file; done
         * run worker program to apply that; done
         */

        ifstream configuration("/etc/BatterYLimiT/config.conf");
        string line, settings_path, charge_limit;

        // get each line
        while (getline(configuration, line)) {
            // check if the first character matches the size of "settings"
            if (line.substr(0, 7) == "setting") {
                // get its name path
                settings_path = line.substr(8, line.length()-1);

                // open settings file
                ifstream setting(settings_path);

                // get value
                getline(setting, line);

                // get charge limit
                if (line.substr(line.length()-2, line.length()-1) != "") {
                    // charge limit value
                    charge_limit = line.substr(line.length()-2, line.length()-1);
                }

                // close file
                setting.close();

                // open runtime file
                ofstream runtime("/etc/BatterYLimiT/.runtime.conf");

                // write charge limit
                runtime << charge_limit;

                // close file
                runtime.close();

            }
        }

        // close the file
        configuration.close();

        // apply changes
        write_limit();

    }

    return 0;
}
