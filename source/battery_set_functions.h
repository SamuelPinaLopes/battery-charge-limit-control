#ifndef BATTERY_SET_FUNCTIONS_H
#define BATTERY_SET_FUNCTIONS_H

#include <string>
#include <cstring>

bool check_words(char* word_passed, std::string expected, bool single_character=false);

bool show_settings();
void save_settings_preset();
void set_default_settings();
void set_limit();
void define_limit();
void rename_preset(std::string preset);
void show_presets();
void use_preset(int index=0, std::string name="default");

#endif
