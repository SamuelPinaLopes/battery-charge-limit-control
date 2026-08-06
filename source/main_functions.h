#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <vector>
#include <filesystem>

std::vector<std::string> get_directories(std::filesystem::path defaultPath);
std::string correct_folder();
std::string get_values(std::string arg);
bool is_set();
void setup();
void write_limit();

#endif