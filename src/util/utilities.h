#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <string>
#include <filesystem>
#include <vector>
#include <optional>

std::string first_line(std::filesystem::path file);

bool check_words(char* word_passed, std::string expected, bool single_character=false);

void write_limit();

void load_file_in_array(std::vector <std::string> *array, std::filesystem::path file_path);

void write_line(std::string content, std::filesystem::path file);

std::optional<std::string> find_line(std::string word, std::filesystem::path file);

void get_file_in_folder(std::vector <std::filesystem::path> *array, std::filesystem::path folder);

void write_file(std::vector <std::string> *array, std::filesystem::path file_path);

bool create_file(std::filesystem::path name);

#endif
