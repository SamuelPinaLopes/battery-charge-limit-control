#include <fstream>
#include <filesystem>
#include <cstring>
#include <vector>

// path to battery charge threshold
std::filesystem::path threshold("/sys/class/power_supply/BAT0/charge_control_end_threshold");

// path to runtime file
std::filesystem::path runtime("/etc/BatterYLimiT/.runtime.conf");

// function to first line of any file
std::string get_value(std::filesystem::path file) {
    std::string line;

    std::fstream somefile( file , std::ios::in);

    std::getline( somefile, line );

    somefile.close();

    return line;
}

// function to write battery limit to charge threshold file
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

// loads a file into an array
void load_array(std::vector <std::string> *array, std::filesystem::path file_path, bool from_file=true) {
    // to read file lines
    std::string line;
    //
    if (from_file == true) {
        // open file
        std::ifstream file(file_path);
        // check if the file is open
        if (file.is_open()) {
            // load each file line into array
            while (getline(file, line)) {
                array->push_back(line);
            }
        }
        // close file
        file.close();
    } else {
        // open file
        std::ofstream file(file_path);
        // loop through each line inside array
        for (int index = 0; index < array->size(); index++) {
            // write line into file
            file << array->at(index) << std::endl;
        }
        file.close();
    }
}
