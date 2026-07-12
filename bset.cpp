#include <iostream>
#include "source/functions.h"

using namespace std;

int main(int argc, char* argv[]) {

    for (int index = 0; index < argc; index++) {
        cout << argv[index] << "    " << endl;
        
        if (argv[index] == "-u" or argv[index] == "--update") {
            apply_updates();
        
        } else if (argv[index] == "-su" or argv[index] == "--search-update") {
            search_updates();

        } else if (argv[index] == "-s" or argv[index] == "--show-settings") {
            show_settings();

        } else if (argv[index] == "-ls" or argv[index] == "--load-settings") {
            load_settings();

        } else if (argv[index] == "-sp" or argv[index] == "--save-preset") {
            save_settings_preset();

        } else if (argv[index] == "-dflt" or argv[index] == "--default-settings") {
            set_default_settings();

        } else if (argv[index] == "-gen" or argv[index] == "--gen-default-config") {
            gen_default_config();
            
        } else if (argv[index] == "-p" or argv[index] == "--show-paths") {
            show_paths();

        }

    }
    
    return 0;
}