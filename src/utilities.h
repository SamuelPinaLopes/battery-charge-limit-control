#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <string>
#include <filesystem>
#include <vector>

std::string get_value(std::filesystem::path file);
bool check_words(char* word_passed, std::string expected, bool single_character=false);
void write_limit();
void load_array(std::vector <std::string> *array, std::filesystem::path file_path, bool from_file=true);
void write(std::filesystem::path file, std::string content);

#endif
