#include <iostream>
#include <filesystem>
#include <vector>
#include "main_functions.h"
#include <fstream>
#include <cstdio>
#include <array>
#include <sstream>


using namespace std;


string power_supply("/sys/class/power_supply/");
string threshold_file("/charge_control_end_threshold");
filesystem::path settings_directory("/etc/BatterYLimiT");
filesystem::path config_file = "/etc/BatterYLimiT/setup.conf";
string service_file("/etc/systemd/system/set-limit.service");
string executable_file("/usr/local/bin/set-limit");

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

    // check if files are there

    // returns the current pc state
    if (get_values("--setup") == "1") {
        // YES, computer is setup
        return true;
    } else {
        // NO, computer isn't setup
        return false;
    }

}

void setup() { // setup all configs
    /* 
    have three main directories such as: 
        - executable folder = /usr/local/bin/set-limit
        - configuration folder = /etc/BatterYLimiT/setup.conf
        - service folder = /etc/systemd/system/set-limit.service
    */

    // check if this directory doesn't exist and file
    if (!filesystem::exists(settings_directory)) {
        // creating the directory
        filesystem::create_directory(settings_directory);    
    }

    // check if this file doesn't exist
    if (!filesystem::exists(config_file)) {
        // creating file
        ofstream config(config_file);
        
        // putting data on it
        config << "already_setup=1\n"
               << "battery_default_folder=" + correct_folder() + "/\n"
               << "default_limit=80\n"
               << "config_path=/etc/BatterYLimiT/setup.conf\n"
               << "service_path=/home/samuel/.config/systemd/user/battery-limit/set-limit.service\n"
               << "run_program_path=/usr/local/bin/set-limit";

        // closing the file
        config.close();
    }

    
    // creates .service file for both cold boot and hibernation states
    if (!filesystem::exists(service_file)) {
        //create file
        ofstream service(service_file);

        service << "[Unit]\n"
                << "Description=Sets battery charge limit\n"
                << "After=multi-user.target hibernate.target\n\n"
                << "[Service]\n"
                << "ExecStart=/usr/local/bin/set-limit\n\n"
                << "[Install]\n"
                << "WantedBy=multi-user.target hibernate.target";

        // closing file
        service.close();

    }

}

void write_limit() { // to write the limit you want
    
    // checking the charge threshold_file
    if (get_values("--get_current_limit") != "80") {

        // open the file to change limit
        fstream threshold(
            "/sys/class/power_supply/BAT0/charge_control_end_threshold",
            ios::out
            |
            ios::in
        );

        if (threshold) {
            // set the value
            threshold << get_values("--default_limit");
    
        }

        // closing the file
        threshold.close();

    }

}

string get_values(string arg) { // get values inside files with python
    array<char, 128> buffer;
    
    string result, line;
    
    line = "/usr/bin/python /home/samuel/coding/battery-limit/source/read-configs.py " + arg;
    
    FILE* pipe = popen(line.c_str(), "r");
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    return result;

}

void update_config_state() {

    if (!filesystem::exists(config_file)) {
        // changes already_setup=0
    } else if (!filesystem::exists(service_file)) {
        // changes already_setup=0
    } else if (!filesystem::exists(executable_file)) {
        // changes already_setup=0
    } else {
        // keep already_setup=1
    }

}