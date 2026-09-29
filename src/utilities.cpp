#include <fstream>
#include <filesystem>
#include <cstring>

// path to battery charge threshold
std::filesystem::path threshold("/sys/class/power_supply/BAT0/charge_control_end_threshold");

// path to runtime file, file containing limit for charge threshold
std::filesystem::path runtime("/etc/BatterYLimiT/.runtime.conf");

// function to first line of any file
std::string get_value(std::filesystem::path file) {
    // open file for reading
    std::fstream somefile( file , std::ios::in);
    std::string line; // variable to store the first line

    std::getline( somefile, line ); // get the first line

    somefile.close(); // close the file
    return line; // return the value
}

// function to write the limit to charge threshold file
void write_limit() {
    // check if threshold and runtime charge limit value aren't matching
    if (get_value(threshold) != get_value(runtime)) {
        // open treshold file for writing
        std::fstream threshold_file( threshold, std::ios::out );
        // makes sure the file is open
        if (threshold_file.is_open()) {
            // write charge limit value into threshold file
            threshold_file << get_value( runtime );
        }
        // closing the file
        threshold_file.close();
    }
}

// check if words are the same
bool check_words(char* word_passed, std::string expected, bool single_character) {
    // when you're passing a group of characters, make sure that you'll pass it as pointer, kinda array of characters
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
