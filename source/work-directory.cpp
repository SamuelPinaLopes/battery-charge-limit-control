#include <iostream>
#include <filesystem>
#include <vector>
#include "workdirectory.h"

using namespace std;

string power_supply("/sys/class/power_supply/");

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

string correct_folder() { // finds the correct one and return the path to it
    vector<string> directories(get_directories(power_supply)); // creating a vector with returned folders from power path

    for (vector<string>::iterator it = directories.begin(); it != directories.end(); ++it) { // loop throught each folder inside power supply
        
        if ((*it).compare(0, 2, "BA") == 0) { // know the correct folder, add another cases, for other laptops, pc, etc.
            return (power_supply.append((*it))); // returning the path for the correct battery folder
        }
    
    }
    
    return "error, no wanted folders found";
}