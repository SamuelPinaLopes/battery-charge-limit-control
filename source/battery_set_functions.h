#ifndef BATTERY_SET_FUNCTIONS_H
#define BATTERY_SET_FUNCTIONS_H

#include <iostream>
#include <string>
#include <cstring>

bool check_words(char* word_passed, std::string expected, bool single_character=false);

bool search_updates();
void apply_updates();
void show_settings();
void load_settings();
void save_settings_preset();
void set_default_settings();
void show_paths();

#endif
