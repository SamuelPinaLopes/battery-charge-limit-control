#include <iostream>
#include <filesystem>
#include <vector>
#include "workdirectory.h"
#include <fstream>

using namespace std;

string power_supply("/sys/class/power_supply/");
filesystem::path config_file = "/etc/BatterYLimiT/setup.conf";

vector<string> get_directories(filesystem::path defaultPath) { // search for folders
    vector<string> all; // array of all directories inside default path

    filesystem::directory_iterator it(defaultPath); // starting the DIRECTORY_iterator and giving its start point
    filesystem::directory_iterator end;             // ending the DIRECTORY_iterator and it has nothing, end == '' so you don't have to pass nothing.

    for (; it != end; ++it) { // loop through the directory_iterator
        filesystem::directory_entry entry = *it; // entry is like a variable that recives the value that it is pointing

        if (entry.is_directory()) { // if is really a directory
            all.push_back(entry.path().filename().string()); // adding all directories inside array to return
        }
    }

    return all; // returning the folders found inside power_supply
}

string correct_folder() { // chooses the correct folder and return the path to it

    vector<string> directories(get_directories(power_supply)); // creating a vector with returned folders from power path

    for (vector<string>::iterator it = directories.begin(); it != directories.end(); ++it) { // loop throught each folder inside power supply
        
        if ((*it).compare(0, 2, "BA") == 0) { // know the correct folder, add another cases, for other laptops, pc, etc.
            return (power_supply.append((*it))); // returning the path for the correct battery folder
        }
    
    }
    
    return "error, no wanted folders found";
}

bool is_set() { // checks if this laptop is already set

    if (filesystem::exists(config_file)) { // checking if it exists
        return true; // if yes, is already set
    } else {
        return false; // if no, set it
    }

}

void setup() {
    // path for settings
    filesystem::path directory = "/etc/BatterYLimiT";

    // check if this directory doesn't exist
    if (!filesystem::exists(directory)) {
        // creating the directory
        filesystem::create_directory(directory);
    }

    // check if this file doesn't exist
    if (!filesystem::exists(config_file)) {
        // creating the file
        ofstream config(config_file);
        
        // putting data on it
        config << "already_setup=1\n"
               << "work_directory=/sys/class/power_supply/BAT0\n"
               << "default_limit=80";

        // closing the file
        config.close();
    
    }
    
    // creates .service file for cold boot

    // creates .servicde file for hibernation

}




