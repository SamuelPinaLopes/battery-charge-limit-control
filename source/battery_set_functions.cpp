//#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

bool check_words(char* word_passed, string expected, bool single_character=false) { // when you're passing a group of characters, make sure that you'll pass it as *, kinda array of characters
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

bool load_settings(int arg_count, char* parameters[]) {
    cout << "load settings as file." << endl;

    // syntax: --load-settings  [path/to/file]  [parameter "flag"]

    /* rececive a path to the file to load;
     * check if file exists;
     * open that file;
     * check if is this programs config file;
     * open config file;
     * rewrite everything inside config file from file;
     * if also show parameter was pass:
     *  show each line being rewritten;
     * else:
     *  show done when it's done;
     * close those files; */

    cout << parameters[2];

    return true;

}

void save_settings_preset() {cout << "save settings as new preset, enter preset name: ";}
void set_default_settings() {cout << "restore settings to default configuration";}
void show_paths() {cout << "these are all paths in use...";}
