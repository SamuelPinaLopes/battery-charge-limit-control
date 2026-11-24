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
void use_preset(int argc=0, char **argv=nullptr);
void define_limit(int argc=0, char **argv=nullptr);
void delete_preset(int argc=0, char **argv=nullptr);
void create_preset(int argc=0, char **argv=nullptr);
void rename_preset(int argc=0, char **argv=nullptr);
void show_current_limit();

#endif
