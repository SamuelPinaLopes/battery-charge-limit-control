#include <fstream>
#include <filesystem>
#include <cstring>
#include <vector>

// battery charge threshold
std::filesystem::path threshold("/sys/class/power_supply/BAT0/charge_control_end_threshold");

// runtime file
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
    if (get_value(threshold) != get_value(runtime)) {
        // write correct battery limit on file
        std::fstream threshold_file( threshold, std::ios::out );

        if (threshold_file.is_open()) {
            threshold_file << get_value( runtime );
        }

        threshold_file.close();
    }
}

// check if words are the same
bool check_words(char* word_passed, std::string expected, bool single_character) {
    // note: when you're passing a group of characters, make sure that you'll pass it as pointer, kinda array of characters
    int index = 0;
    if (strlen(word_passed) == expected.length()) {
        // check for each character
        while (true) {
            if (word_passed[index] != expected[index]) {
                return false;
            }
            // if it reaches end
            if (word_passed[index] == '\0') {
                return true;
            }
            index++;
        }
    } else {
        return false;
    }
}

// loads a file into an array
void load_array(std::vector <std::string> *array, std::filesystem::path file_path, bool from_file=true) {
    std::string line;
    // this has two sides, one for reading and loading an array and another to write the array into the file
    // true:    loads an array with the file
    // false:   writes everything inside array into file
    if (from_file == true) {
        std::ifstream file(file_path);
        if (file.is_open()) {
            while (getline(file, line)) {
                array->push_back(line);
            }
        }
        file.close();
    } else {
        std::ofstream file(file_path);
        for (int index = 0; index < array->size(); index++) {
            file << array->at(index) << std::endl;
        }
        file.close();
    }
}

// writes value into file
void write(std::string content, std::filesystem::path file) {
    std::ofstream somefile(file);

    somefile << content << std::endl;

    somefile.close();

}
