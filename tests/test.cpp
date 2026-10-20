#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "../src/util/utilities.h"
//#include "../src/param/param_util/header.h"
//#include "../src/param/parameters.h"
#include <stdlib.h>

using namespace std;

//filesystem::path presets_folder("/etc/BatterYLimiT/presets/"), config_file("/etc/BatterYLimiT/config.conf");

int main(int argc, char **argv) {
    
    if (argc > 1) {
        write_limit();
        cout << first_line("/sys/class/power_supply/BAT0/charge_control_end_threshold") << endl << endl;
        cout << system("cat /sys/class/power_supply/BAT0/charge_control_end_threshold");

    } else {
        cout << "no parameters passed!" << endl;

    }

    return 0;

}
