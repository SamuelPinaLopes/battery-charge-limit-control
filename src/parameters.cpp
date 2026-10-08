#include "parameters.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

filesystem::path config_file = "/etc/BatterYLimiT/config.conf",
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

    ifstream default_config(default_config_file);

    getline(default_config, line);

    charge_limit_value = line.substr(line.length()-2, 2);

    while (getline(default_config, line)) {
        if (line.substr(0, 7) == "setting") {
            configpath = line.substr(8, line.length()-1);
        }
    }

    default_config.close();

    /* write limit value into runtime file */
    ofstream runtime(runtime_file);
    runtime << charge_limit_value;
    runtime.close();

    /* load each line from config file into array */
    load_array(&array, configpath);

    /* replace old value and path to new ones */
    array[0] = array[0].substr( 0, array[0].length()-2 );
    array[1] = array[1].substr(0, 8);
    array[0].append(charge_limit_value);
    array[1].append(configpath);

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

    write(runtime_file, new_battery_limit);

    /* apply new battery limit */
    write_limit();

    /* rewrite default battery limit back to file */
    write(runtime_file, old_battery_limit);

    cout << "\n\nold battery limit: " << old_battery_limit << endl
         << "current battery limit: " << get_value(threshold_file) << endl;
}

void show_presets(bool arr, std::vector <std::filesystem::path> *array) {
    int count = 1;

    filesystem::path path(presets_folder);
    // if array or true: fill array with avaiable presets
    // else empty array or false: show all presets avaiable
    if (array == nullptr or arr == false) {
        cout << "presets list: \n";

        for (const auto entry : filesystem::directory_iterator(path)) {
            cout << count
                 << " == "
                 << string( entry.path() ).substr(
                    string(presets_folder).length(),
                    string( entry.path() ).length() - 1
                 )
                << endl;

            count++;
        }
    } else {
        for (const std::filesystem::path entry : filesystem::directory_iterator(path)) {
           array->push_back(entry);
        }
    }
}

void use_preset() {
    string selected, line, oldpath, presetpath;
    vector <string> array;
    vector <filesystem::path> presets_array;

    show_presets();

    cout << "input preset number: ";
    cin >> selected;

    ifstream config(config_file);
    while (getline(config, line)) {
        array.push_back(line);
    }
    config.close();

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

    ofstream config2(config_file);
    for (int index = 0; index < array.size(); index++) {
        config2 << array[index] << endl;
    }
    config2.close();

    ifstream file(presetpath);
    getline(file, line);
    line = line.substr(line.length()-2, line.length()-1);
    file.close();

    ofstream runtime(runtime_file);
    runtime << line;
    runtime.close();

    /* apply battery limit */
    write_limit();

    cout << "used: " << oldpath << endl
         << "preset chosen: " << presetpath[stoi(selected)-1] << endl;
}

void define_limit() {
    string line, filepath, newlimit, oldlimit;
    vector <string> array;

    ifstream config(config_file);
    if (config.is_open()) {
        while (getline(config, line)) {
            if (line.substr(0, 7) == "setting") {
                break;
            }
        }
    }
    config.close();

    /* extract file path */
    filepath = line.substr(8, line.length()-1);

    cout << "\nsettings currentely using: " << line.substr(string("setting=/etc/BatterYLimiT/").length(), line.length()-1) << endl;
    cout << "insert new battery charge limit: ";
    cin >> newlimit;

    ifstream settingsfile(filepath);
    if (settingsfile.is_open()) {
        while (getline(settingsfile, line)) {
            array.push_back(line);
        }
    }
    settingsfile.close();

    oldlimit = array[0].substr(array[0].length()-2, array[0].length()-1);
    /* remove old battery limit */
    array[0] = array[0].substr(0, array[0].length()-2);
    array[0].append(newlimit);

    ofstream settingsfile2(filepath);
    for (int index = 0; index < array.size(); index++) {
        settingsfile2 << array[index] << endl;
    }
    settingsfile2.close();

    /* show the full file */
    cout << "--------------------------------------"
         << "\nold limit: " << oldlimit
         << "\nnew limit: " << newlimit
         << "\n\nfull settings:" << endl;
    ifstream settingsfile3(filepath);
    while (getline(settingsfile3, line)) {
        cout << line << endl;
    }
    settingsfile3.close();
}
