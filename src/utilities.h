#ifndef WORKDIRECTORY_H
#define WORKDIRECTORY_H

#include <string>
#include <filesystem>

std::string get_value(std::filesystem::path file);
void write_limit();

#endif
