#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <string>
#include <filesystem>
#include <vector>

std::string get_value(std::filesystem::path file);
bool check_words(char* word_passed, std::string expected, bool single_character=false);
void write_limit();
void load_array(std::vector <std::string> *array, std::filesystem::path file_path, bool from_file=true);
void write(std::string content, std::filesystem::path file);
std::string find_line(std::string word, std::filesystem::path file);

void load_preset_path(std::vector <std::filesystem::path> *array);
void write_file(std::vector <std::string> *array, std::filesystem::path file_path);

#endif
