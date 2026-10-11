#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <string>
#include <filesystem>
#include <vector>
#include <optional>

std::string first_line(std::filesystem::path file);

bool check_words(char* word_passed, std::string expected, bool single_character=false);

void write_limit();

void load_array(std::vector <std::string> *array, std::filesystem::path file_path, bool from_file=true);

void write_line(std::string content, std::filesystem::path file);

std::optional<std::string> find_line(std::string word, std::filesystem::path file);

void file_path(std::vector <std::filesystem::path> *array, std::filesystem::path folder);

void write_file(std::vector <std::string> *array, std::filesystem::path file_path);

#endif
