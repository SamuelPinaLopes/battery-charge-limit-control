#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <vector>
#include <filesystem>

std::vector<std::string> get_directories(std::filesystem::path defaultPath);
std::string correct_folder();
bool is_set();
void setup();
bool write_limit();

#endif