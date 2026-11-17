#include "parameters.h"
#include "param_util/util.h"
#include "../util/utilities.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;

filesystem::path config_file("/etc/BatterYLimiT/config.conf"),
presets_folder("/etc/BatterYLimiT/presets/"),
runtime_file("/etc/BatterYLimiT/.runtime.conf"),
default_config_file("/etc/BatterYLimiT/.default.conf"),
threshold_file("/sys/class/power_supply/BAT0/charge_control_end_threshold");

void show_settings() {
    cout << "Current Settings:\n\n";
    show_file(config_file);
}

void save_settings_preset() {
    string preset_name, limit, full_path;

    // create a function to check user inputs AND through its execptions!
    cout << "enter preset name: ";
    cin >> preset_name;

    // create a function to check user inputs AND through its execptions!
    cout << "enter limit value: ";
    cin >> limit;

    /* check if preset name has an extension, if not add */
    if (preset_name.length() >= 5) {
        if (preset_name.substr(preset_name.length() - 5, 5) != ".conf") {
            preset_name = preset_name + ".conf";
        }
    } else {
        preset_name = preset_name + ".conf";
    }

    full_path = presets_folder.string() + preset_name;

    /* remove preset with same name */
    for (auto const& entry : filesystem::directory_iterator(presets_folder)) {
        if (full_path == entry.path()) {
            remove(entry.path().c_str());
        }
    }

    create_file(full_path);
    
    write_line("charge_limit=" + limit, full_path);

    cout << preset_name << " created!" << endl;
}

void set_default_settings() {
    vector <string> array;

    load_file_in_array(&array, config_file);

    /* replace old value and path to new ones */
    array[0] = array[0].substr( 0, array[0].length()-2 );
    array[1] = array[1].substr(0, 8);
    array[0].append("80");
    array[1].append(config_file);

    /* write each line inside array into file */
    write_file(&array, config_file);

    /* write default battery limit */
    write_limit();
}

void set_limit() {
    string new_battery_limit, old_battery_limit;

    // create a function to check user inputs AND through its execptions!
    cout << "new charge limit: ";
    cin >> new_battery_limit;

    old_battery_limit = first_line(threshold_file);

    /* apply new battery limit */
    write_limit(new_battery_limit);

    cout << "\n\nold battery limit: " << old_battery_limit << endl
         << "current battery limit: " << first_line(threshold_file) << endl;
}

void show_presets() {
    int count = 1;
    for (const auto entry : filesystem::directory_iterator(presets_folder)) {
        cout << count
            << " == "
            << string( entry.path() ).substr( string(presets_folder).length() )
            << endl;
        count++;
    }
}

void use_preset() {
    string selected, battery_limit, oldpath, presetpath;
    vector <string> array;
    vector <filesystem::path> presets_array;

    // create a function to check user inputs AND through its execptions!
    cout << "input preset number: ";
    cin >> selected;

    load_file_in_array(&array, config_file);

    /* get each preset file path */
    get_file_in_folder(&presets_array, presets_folder);

    presetpath = presets_array[stoi(selected)-1];

    for (int index = 0; index < array.size(); index++) {
        if (array[index].substr(0, 7) == "setting") {
            oldpath = array[index].substr(0, 8);

            // remove old path
            array[index] = array[index].substr(0, 8);

            array[index].append(presetpath);
            break;
        }
    }

    write_file(&array, config_file);

    battery_limit = first_line(presetpath);

    /* apply new battery limit */
    write_limit(
        battery_limit.substr( battery_limit.length()-2 )
    );

    cout << "used: " << oldpath << endl
         << "now in use: " << presetpath[stoi(selected)-1] << endl;
}

void define_limit() {
    string newlimit, oldlimit;
    vector <string> array;

    // create a function to check user inputs AND through its execptions!
    cout << "insert new battery limit: ";
    cin >> newlimit;

    oldlimit = first_line(config_file);

    load_file_in_array(&array, config_file);

    /* remove old battery limit */
    array[0] = array[0].substr(0, array[0].length()-2);
    array[0].append(newlimit);

    /* write array back to file */
    write_file(&array, config_file);

    /* show the full file */
    cout << "--------------------------------------"
         << "\nold limit: " << oldlimit
         << "\nnew limit: " << newlimit
         << "\n\nfull settings:" << endl;

    show_file(config_file);
}

void delete_preset() {
    vector <filesystem::path> presets;
    int file;

    get_file_in_folder(&presets, presets_folder);

    for (int index = 0; index < presets.size(); index++) {
        cout << index + 1
            << " == "
            << presets[index]
            << endl;
    }

    // create a function to check user inputs AND through its execptions!
    cout << "which file: ";
    cin >> file;

    if ( remove(presets[file-1].c_str()) ) {
        cout << "file removed:"
            << "\n"
            << presets[file]
            << endl;
    }
}

void create_preset() {
    string name, limit;
    filesystem::path path;

    // create a function to check user inputs AND through its execptions!
    cout << "preset name: ";
    cin >> name;
    cout << "battery limit: ";
    cin >> limit;

    name = presets_folder.string() + name;

    create_file(name);

    write_line(limit, name);
}

void rename_preset() {
    string selected, name;
    vector <filesystem::path> presets;

    get_file_in_folder(&presets, presets_folder);

    show_presets();

    // create a function to check user inputs AND through its execptions!
    cout << "select preset to rename: ";
    cin >> selected;

    cout << "enter new name: ";
    cin >> name;

    filesystem::rename(
        presets.at(stoi(selected)-1),
        presets_folder.string() + name
    );

    cout << "\npresets avaiable: " << endl;

    show_presets();
}

void show_current_limit() {
    cout << "Battery Limit Currently in use:\n"
        << first_line(threshold_file)
        << endl;
}
