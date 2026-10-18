#ifndef BATTERY_SET_FUNCTIONS_H
#define BATTERY_SET_FUNCTIONS_H

#include <filesystem>
#include <string>
#include <cstring>
#include <vector>

void show_settings();
void save_settings_preset();
void set_default_settings();
void set_limit();
void show_presets();
void use_preset();
void define_limit();
void delete_preset();
void create_preset();

#endif
