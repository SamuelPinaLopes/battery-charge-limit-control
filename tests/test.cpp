#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "../src/util/utilities.h"
#include "../src/param/param_util/header.h"
#include "../src/param/parameters.h"

using namespace std;

//filesystem::path presets_folder("/etc/BatterYLimiT/presets/"), config_file("/etc/BatterYLimiT/config.conf");

int main(int argc, char **argv) {
    
    if (argc > 1) {
       
        if (check_words(argv[1], "r")) {
            rename_preset();
        }

        if (check_words(argv[1], "c")) {
            create_preset();
        }

        if (check_words(argv[1], "d")) { 
            delete_preset();
        }

    } else {
        cout << "no parameters passed!" << endl;
    }

    return 0;

}
