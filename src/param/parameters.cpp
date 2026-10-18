#include "parameters.h"
#include "../util/utilities.h"
#include "param_util/header.h"
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

    full_path = presets_folder.string() + preset_name;

    /* remove preset with same name */
    for (auto const& entry : filesystem::directory_iterator(presets_folder)) {
        if ((presets_folder.string() + preset_name) == entry.path()) {
            remove(entry.path().c_str());
        }
    }

    if (create_file(full_path)) {
        write_line("charge_limit=" + limit, full_path);
        cout << preset_name << " created!" << endl;

    } else {
        cout << "error creating new preset!" << endl;

    }
}

void set_default_settings() {
    string line, charge_limit_value;
    vector <string> array;

    charge_limit_value = first_line(default_config_file).substr(line.length()-2);

    /* write limit value into runtime file */
    write_line(runtime_file, charge_limit_value);

    load_file_in_array(&array, config_file);

    /* replace old value and path to new ones */
    array[0] = array[0].substr( 0, array[0].length()-2 );
    array[1] = array[1].substr(0, 8);
    array[0].append(charge_limit_value);
    array[1].append(config_file);

    /* write each line inside array into file */
    write_file(&array, config_file);

    /* reload battery charge limit */
    write_limit();
}

void set_limit() {
    string new_battery_limit, old_battery_limit;

    cout << "new charge limit: ";
    getline(cin, new_battery_limit);

    old_battery_limit = first_line(threshold_file);

    write_line(new_battery_limit, runtime_file);

    /* apply new battery limit */
    write_limit();

    /* rewrite default battery limit back to file */
    write_line(old_battery_limit, runtime_file);

    cout << "\n\nold battery limit: " << old_battery_limit << endl
         << "current battery limit: " << first_line(threshold_file) << endl;
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

    write_line(
        battery_limit.substr(battery_limit.length()-2),
        runtime_file
    );

    /* apply battery limit */
    write_limit();

    cout << "used: " << oldpath << endl
         << "preset chosen: " << presetpath[stoi(selected)-1] << endl;
}

void define_limit() {
    string newlimit, oldlimit;
    vector <string> array;

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




}
