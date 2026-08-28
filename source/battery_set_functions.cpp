#include <iostream>
#include <string>
#include <cstring>

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

bool search_updates() {cout << "fetching for updates..."; return 0;}
void apply_updates() {cout << "applying updates...";}
void show_settings() {cout << "show current settings.";}
void load_settings() {cout << "load settings preset.";}
void save_settings_preset() {cout << "save settings as new preset, enter preset name: ";}
void set_default_settings() {cout << "restore settings to default configuration";}
void show_paths() {cout << "these are all paths in use...";}