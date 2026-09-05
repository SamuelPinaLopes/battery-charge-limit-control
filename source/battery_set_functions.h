#ifndef BATTERY_SET_FUNCTIONS_H
#define BATTERY_SET_FUNCTIONS_H

#include <iostream>
#include <string>
#include <cstring>

bool check_words(char* word_passed, std::string expected, bool single_character=false);

bool show_settings();
bool load_settings(int arg_count, char* parameters[]);
void save_settings_preset();
void set_default_settings();
void show_paths();
void set_limit(int value = 80);

#endif
