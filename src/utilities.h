#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <string>
#include <filesystem>

std::string get_value(std::filesystem::path file);
bool check_words(char* word_passed, std::string expected, bool single_character=false);
void write_limit();

#endif
