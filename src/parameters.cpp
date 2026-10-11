#include "parameters.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

filesystem::path config_file("/etc/BatterYLimiT/config.conf"),
presets_folder("/etc/BatterYLimiT/presets/"),
runtime_file("/etc/BatterYLimiT/.runtime.conf"),
default_config_file("/etc/BatterYLimiT/.default.conf"),
threshold_file("/sys/class/power_supply/BAT0/charge_control_end_threshold");

void show_settings() {
    string lines;
    ifstream read_settings(config_file);

    if (read_settings.is_open() == true) {
        cout << "Current Settings:\n\n";

        while (getline(read_settings, lines)) {
            cout << lines << endl;
        }
    }
    read_settings.close();
}

void save_settings_preset() {
    string preset_name, limit;

    cout << "enter preset name: ";
    getline(cin, preset_name);

    cout << "enter limit value: ";
    getline(cin, limit);

    /* check if preset name has an extension, if not add */
    if (preset_name.length() >= 5) {
        if (preset_name.substr(preset_name.length() - 5, 5) != ".conf") {
            preset_name = preset_name + ".conf";
        }
    } else {
        preset_name = preset_name + ".conf";
    }

    /* remove preset with same name */
    for (auto const& entry : filesystem::directory_iterator(presets_folder)) {
        if ((presets_folder.string() + preset_name) == entry.path()) {
            remove(entry.path().c_str());
        }
    }

    /* creating new preset from config file */
    ofstream preset(presets_folder.string() + preset_name);
    if (preset.is_open()) {
        preset << "charge_limit="  << limit << endl;
        // show info
        cout << "\n"
             << "preset created!" << endl
             << "preset path: "
             <<  presets_folder.string() + preset_name << endl;
    } else {
        cout << "error creating new preset!" << endl;
    }
    preset.close();
}

void set_default_settings() {
    string line, charge_limit_value, configpath;
    vector <string> array;

    charge_limit_value = get_value(default_config_file).substr(line.length()-2, 2);

    /* write limit value into runtime file */
    write(runtime_file, charge_limit_value);

    load_array(&array, configpath);

    /* replace old value and path to new ones */
    array[0] = array[0].substr( 0, array[0].length()-2 );
    array[1] = array[1].substr(0, 8);
    array[0].append(charge_limit_value);
    array[1].append(config_file);

    /* write each line inside array into file */
    load_array(&array, configpath, false);

    /* reload battery charge limit */
    write_limit();
}

void set_limit() {
    string new_battery_limit, old_battery_limit;

    cout << "new charge limit: ";
    getline(cin, new_battery_limit);

    old_battery_limit = get_value(threshold_file);

    write(new_battery_limit, runtime_file);

    /* apply new battery limit */
    write_limit();

    /* rewrite default battery limit back to file */
    write(old_battery_limit, runtime_file);

    cout << "\n\nold battery limit: " << old_battery_limit << endl
         << "current battery limit: " << get_value(threshold_file) << endl;
}

void show_presets() {
    int count = 1;

    for (const auto entry : filesystem::directory_iterator(presets_folder)) {
        cout    << count
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

    show_presets();

    cout << "input preset number: ";
    cin >> selected;

    load_array(&array, config_file);

    /* get each preset file path */
    show_presets(true, &presets_array);

    for (int index = 0; index < array.size(); index++) {
        if (array[index].substr(0, 7) == "setting") {
            oldpath = array[index].substr(0, 8);

            // remove old path
            array[index] = array[index].substr(0, 8);

            presetpath = presets_array[stoi(selected)-1];
            array[index].append(presetpath);
            break;
        }
    }

    load_array(&array, config_file, false);

    battery_limit = get_value(presetpath);

    write(battery_limit, runtime_file);

    /* apply battery limit */
    write_limit();

    cout << "used: " << oldpath << endl
         << "preset chosen: " << presetpath[stoi(selected)-1] << endl;
}

void define_limit() {
    string line, configpath, newlimit, oldlimit;
    vector <string> array;

    cout << "insert new battery limit: ";
    cin >> newlimit;

    oldlimit = get_value(config_file);

    load_array(&array, config_file);

    /* remove old battery limit */
    array[0] = array[0].substr(0, array[0].length()-2);
    array[0].append(newlimit);

    /* write array back to file */
    load_array(&array, config_file, false);

    /* show the full file */
    cout << "--------------------------------------"
         << "\nold limit: " << oldlimit
         << "\nnew limit: " << newlimit
         << "\n\nfull settings:" << endl;

    ifstream file(config_file);
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
