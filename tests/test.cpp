#include <iostream>
#include <string>
// #include <filesystem>
// #include <vector>
#include "../src/util/utilities.h"
#include "../src/param/parameters.h"
#include "../src/param/param_util/util.h"
//#include <stdlib.h>

using namespace std;

//filesystem::path presets_folder("/etc/BatterYLimiT/presets/"),
//config_file("/etc/BatterYLimiT/config.conf");

int main(int argc, char **argv) {


    if (argc > 1) {
        //write_limit();
        //cout << first_line("/sys/class/power_supply/BAT0/charge_control_end_threshold")
        //<< endl << endl;
        //cout << system("cat /sys/class/power_supply/BAT0/charge_control_end_threshold");
        
        //show_current_limit();
        // show_presets();

        // rename_preset(argc, argv);
    
        // create_preset(argc, argv);

        if (check_words(argv[1], "--create-preset") == true) {
            create_preset(argc, argv);
        }
        if (check_words(argv[1], "--rename")) {
            rename_preset(argc, argv);
        }
        if (check_words(argv[1], "--delete"))
            delete_preset(argc, argv);

        if (check_words(argv[1], "--new-limit"))
            define_limit(argc, argv);
        
        if (check_words(argv[1], "--select-preset"))
            use_preset(argc, argv);

        
        if (check_words(argv[1], "--show-preset")) {
            show_presets();
        }

    } else {
        std::cout << "no parameters passed!" << std::endl;

    }

    return 0;

}
