#ifndef BATTERY_SET_FUNCTIONS_H
#define BATTERY_SET_FUNCTIONS_H

#include <filesystem>
#include <string>
#include <cstring>
#include <vector>

bool check_words(char* word_passed, std::string expected, bool single_character=false);

void show_settings();
void save_settings_preset();
void set_default_settings();
void set_limit();
void show_presets(std::vector <std::filesystem::path>* array=nullptr, bool arr=false);
void use_preset();
void define_limit();
void rename_preset(std::string preset);

#endif
