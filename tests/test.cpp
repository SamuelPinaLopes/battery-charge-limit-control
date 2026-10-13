#include <iostream>
#include <string>
#include <filesystem>
//#include "../src/util/utilities.h"
//#include <vector>
#include "../src/param/param_util/header.h"

using namespace std;

filesystem::path presets_folder("/etc/BatterYLimiT/presets/"),
    config_file("/etc/BatterYLimiT/config.conf");

int main(int argc, char **argv) {
    
    show_file(config_file);

    return 0;

}
