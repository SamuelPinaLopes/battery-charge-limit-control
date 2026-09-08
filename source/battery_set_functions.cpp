#include "battery_set_functions.h"
#include <iostream>
#include <string>

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
    /*
     * copy program's config to presets folder;
     * rename config inside presets folder;
     * show the process or just done when it ends;
     */

    string variable = "/etc/BatterYLimiT/config.conf";

    cout << "save settings as new preset, enter preset name: ";
}
void set_default_settings() {cout << "restore settings to default configuration";}
void set_limit(int value) {cout << "setup the charge threshold to: " << value << endl;}
void define_limit() {cout << "define charge limit" << endl;}
void rename_preset(string preset) {cout << "renaming preset: " << preset << endl;}
void show_presets() {cout << "presets list:" << endl;}
void use_preset(int index, string name) {cout << "preset choosen: " << name << endl;}
