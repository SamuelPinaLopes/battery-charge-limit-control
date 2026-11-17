#include <fstream>
#include <filesystem>
#include <cstring>
#include <vector>
#include <string>
#include <optional>
#include <stdexcept>

std::filesystem::path threshold("/sys/class/power_supply/BAT0/charge_control_end_threshold");

// function to first line of any file
std::string first_line(std::filesystem::path file) {
    std::string line;

    std::fstream somefile( file , std::ios::in);

    if (somefile.is_open() == false) {
        throw std::runtime_error("fail to open file...\nfile: " + file.string());
    }

    std::getline(somefile, line);

    somefile.close();

    return line;
}

// function to write battery limit to charge threshold file
void write_limit() {
    std::ofstream threshold_file(threshold);

    if (threshold_file.is_open() == false) {
        throw std::runtime_error("fail to write battery charge limit value");
    }

    if (first_line(threshold) != first_line(runtime)) {
        // write correct battery limit on file
        threshold_file << first_line( runtime );
    }

    threshold_file.close();
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
void load_file_in_array(std::vector <std::string> *array, std::filesystem::path file_path) {
    // loads each file line into array
    std::string line;
    std::ifstream file(file_path);

    if (file.is_open() == false) {
        throw std::runtime_error("fail to open file to load array!\nfile path: " + file_path.string());
    }

    if (array == nullptr) {
        throw std::invalid_argument("invalid array to save file lines!\nNullPtr array.");
    }

    if (file.is_open() == true) {
        while (getline(file, line)) {
            array->push_back(line);
        }
    }

    file.close();
}

// writes value into file
void write_line(std::string content, std::filesystem::path file) {
    std::ofstream somefile(file);

    if (somefile.is_open() == false) {
        throw std::runtime_error("fail to open file to write one line on it!\nfile path: " + file.string());
    }

    somefile << content << std::endl;

    somefile.close();
}

// returns line with matching string
std::optional<std::string> find_line(std::string word, std::filesystem::path file) {
    std::string line;

    std::ifstream somefile(file);

    if (somefile.is_open() == false) {
        throw std::runtime_error("file to open file to find a word!\nfile path: " + file.string());
    }

    while (getline(somefile, line)) {
        if (line.find(word) != std::string::npos) {
            somefile.close();
            return line;
        }
    }

    somefile.close();

    return std::nullopt;
}

// loads an array with all files inside a folder
void get_file_in_folder(std::vector<std::filesystem::path> *array, std::filesystem::path folder) {
    if (array == nullptr) {
        throw std::invalid_argument("invalid array to load with available files inside folder!\nNullPtr array");
    }
    for (const std::filesystem::path entry : std::filesystem::directory_iterator(folder)) {
        array->push_back(entry);
    }
}

// writes all contents inside an array into a file
void write_file(std::vector<std::string> *array, std::filesystem::path file_path) {
    std::ofstream file(file_path);

    if (file.is_open() == false) {
        throw std::runtime_error("file to write an array into file!\nfile path: " + file_path.string());
    }

    if (array == nullptr) {
        throw std::invalid_argument("impossible write a file into a nullptr array!");
    }

    for (int index = 0; index < array->size(); index++) {
        file << array->at(index) << std::endl;
    }

    file.close();
}

void create_file(std::filesystem::path name) {
    std::ofstream somefile(name);

    if (somefile.is_open() == false) {
        throw std::runtime_error("cannot create file!\nfile path => " + name.string());
    }

    somefile.close();
}
