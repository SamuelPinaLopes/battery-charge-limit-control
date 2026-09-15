#include <iostream>
#include "battery_set_functions.h"
#include <ostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdio>

using namespace std;

bool check_words(char* word_passed, string expected, bool single_character) { // when you're passing a group of characters, make sure that you'll pass it as *, kinda array of characters
    // loop through each character position
    int index = 0;

    // if the size are the same
    if (strlen(word_passed) == expected.length()) {

        while (true) {

            // check each character
            if (word_passed[index] != expected[index]) {
                // the words aren't the same
                return false;
            }
            // when it ends
            if (word_passed[index] == '\0') {
                return true;
            }
            // incrementing characters position
            index++;

        }

    } else {
        return false;
    }

}

bool show_settings() {
    ifstream read_settings("/etc/BatterYLimiT/config.conf");
    string lines;
    /* open the settings file;
     * read each line until finding what you want;
     * show it;
     * close the file */

    // openning file with settings on it
    // check if the file is open
    if (read_settings.is_open() == true) {
        cout << "Current Settings:\n\n";
        // loop through each line to get the lines with getline method
        while (getline(read_settings, lines)) {
            // print that line
            cout << lines << endl;
        }
        // close the file
        read_settings.close();
        // did fine
        return true;
    } else {
        // something went wront
        return false;
    }

}

void save_settings_preset() {
    /* ask for the preset name; done
     * check if it has an extension, if not add it; done
     * check if another file does not have the same name (if has same name, replace that file with this new one); done
     * ask the system to copy as root;
     * copy program's config to presets folder;
     * show if it worked or not; */

    string preset_name;
    string config_file("/etc/BatterYLimiT/config.conf");

    filesystem::path p = filesystem::current_path(); // gives you the path from where the program is running
    string path(string(p) + "/preset/");

    /* entering preset name */
    cout << "enter preset name: ";
    cin >> preset_name;

    /* checking if preset name has an extension */
    // if word has a size to have an extension
    if (preset_name.length() >= 5) {
        // if word doesn't have extension, add it
        if (preset_name.substr(preset_name.length() - 5, 5) != ".conf") {
            preset_name = preset_name + ".conf";
        }
    // adding extension if is too short to have one
    } else {
        preset_name = preset_name + ".conf";
    }

    /* check if the name is already in use in preset folder */
    // for each file inside preset directory
    for (auto const& entry : filesystem::directory_iterator(path)) {
        // if preset name is already in use
        if ((path + preset_name) == entry.path()) {
            // removing that file
            remove(entry.path().c_str());
        }
    }

    /* creating new preset from config file */
    if (filesystem::copy_file(config_file, path + preset_name)) {
        cout << "preset created!" << endl;
    } else {
        cout << "error creating new preset!" << endl;
    }

}

void set_default_settings() {cout << "restore settings to default configuration";}
void set_limit(int value) {cout << "setup the charge threshold to: " << value << endl;}
void define_limit() {cout << "define charge limit" << endl;}
void rename_preset(string preset) {cout << "renaming preset: " << preset << endl;}
void show_presets() {cout << "presets list:" << endl;}
void use_preset(int index, string name) {cout << "preset choosen: " << name << endl;}
