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
default_config_file("/etc/BatterYLimiT/.default.conf"),
threshold_file("/sys/class/power_supply/BAT0/charge_control_end_threshold");

void show_settings() {
    cout << "Current Settings:\n\n";
    show_file(config_file);
}

void save_settings_preset(int argc, char **argv) {
    string preset_name, limit, full_path;
    if (argc > 2) {
        for (int index = 0; index < argc; index++) {
            if (string(argv[index]).find("name=") != string::npos) {
                preset_name = string(argv[index]).substr(string("name=").size());

                limit = first_line(threshold_file);

                full_path = presets_folder.string() + preset_name;

                create_file(full_path);

                //write_line("charge_limit=" + limit, full_path); add extra parameter for this!

                cout << preset_name << " created!" << endl;

                break;
            }
        }
    } else {
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

void set_limit(int argc, char **argv) {
    string new_battery_limit, old_battery_limit;
    if (argc > 2) {
        for (int index = 0; index < argc; index++) {
            if (index > 1) {
                // if return is std::string::npos, it means not found
                if (string(argv[index]).find("limit=") != std::string::npos) {
                    new_battery_limit = string(argv[index]).substr(string("limit=").size());
                    cout << "new limit: " << new_battery_limit << endl;
                }
                old_battery_limit = first_line(threshold_file);
                write_limit(new_battery_limit);
                cout << "\n\nold battery limit: " << old_battery_limit << endl
                     << "current battery limit: " << first_line(threshold_file) << endl;
                break;
            }
        }
    } else {
        // create a function to check user inputs AND through its execptions!
        cout << "new charge limit: ";
        cin >> new_battery_limit;

        old_battery_limit = first_line(threshold_file);

        /* apply new battery limit */
        write_limit(new_battery_limit);

        cout << "\n\nold battery limit: " << old_battery_limit << endl
             << "current battery limit: " << first_line(threshold_file) << endl;
    }
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

void use_preset(int argc, char **argv) {
    string preset, presetpath, oldpath, battery_limit;
    vector<string> config;
    vector<std::filesystem::path> preset_array;

    if (argc > 2) {
        for (int index = 0; index < argc; index++) {
            if (index > 1) {
                // if return is std::string::npos, it means not found
                if (string(argv[index]).find("name=") != std::string::npos) {
                    preset = string(argv[index]).substr(string("name=").size());
                }
                break;
            }
        }

        load_file_in_array(&config, config_file);

        /* get each preset file path to check if file exists */
        get_file_in_folder(&preset_array, presets_folder);

        for (auto ps : preset_array) {
            if (string(ps).find(preset) != string::npos) {
                presetpath = ps;

                for (int index = 0; index < config.size(); index++) {
                    if (config[index].find("setting") != string::npos) {
                        oldpath = config[index].substr(config[index].find("=")+1);
                        config[index].erase(config[index].find("=")+1);
                        config[index].append(presets_folder.string() + preset);
                        break;
                    }
                }

                write_file(&config, config_file);

                battery_limit = first_line(presetpath);

                //write_limit(battery_limit); extra parameter, apply it now

                cout << "used: " << oldpath.substr(oldpath.rfind("/")+1) << endl << "now in use: " << preset << endl;

                break;
            }
        }
    } else {
        string selected;
        vector <string> array;
        vector <filesystem::path> presets_array;

        show_presets();

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
}

void define_limit(int argc, char **argv) {
    if (argc > 2) {
        string newlimit, oldlimit;
        vector<string> array;

        for (int index = 0; index < argc; index++) {
            if (index > 1) {
                // if return is std::string::npos, it means not found
                if (string(argv[index]).find("limit=") != std::string::npos) {
                    newlimit = string(argv[index]).substr(string("limit=").size());
                }
            }
        }
        cout << "this is the value to put as new limit: " << newlimit << endl;

        oldlimit = first_line(config_file);

        load_file_in_array(&array, config_file);

        //array[0] = array[0].substr(0, array[0].rfind("=")+1);
        array[0] = array[0].erase(array[0].rfind("=")+1);
        cout << "\n line file cutted:\n" << array[0] << endl;
        array[0].append(newlimit);

        write_file(&array, config_file);

        cout << "--------------------------------------"
        << "\nold limit: " << oldlimit.substr(oldlimit.rfind("=")+1)
        << "\nnew limit: " << newlimit
        << "\n\nfull settings:" << endl;

        show_file(config_file);
    } else {
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
}

void delete_preset(int argc, char **argv) {
    if (argc > 2) {
        bool arg1;
        string name;

        for (int index = 0; index < argc; index++) {
            if (index > 1) {
                // if return is std::string::npos, it means not found
                if (string(argv[index]).find("name=") != std::string::npos) {
                    name = string(argv[index]).substr(string("name=").size());
                    filesystem::remove(string(presets_folder) + name);
                    break;
                }
            }
        }

    } else {
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
}

void create_preset(int argc, char **argv) {
    if (argc > 2) {
        bool arg1, arg2;
        string name, limit;

        for (int index = 0; index < argc; index++) {
            if (index > 1) {
                // if return is std::string::npos, it means not found
                if (string(argv[index]).find("name=") != std::string::npos) {
                    arg1 = true;
                    name = string(argv[index]).substr(string("name=").size());
                }
                if (string(argv[index]).find("limit=") != std::string::npos) {
                    arg2 = true;
                    limit = string(argv[index]).substr(string("limit=").size());
                }
            }
        }

        if (arg1 and arg2) {
            name = presets_folder.string() + name;

            create_file(name);

            write_line(limit, name);

            show_presets();
        }

    } else {
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

        cout << "\npreset list:" << endl;
        show_presets();
    }
}

void rename_preset(int argc, char **argv) {
    if (argc > 2) {
        bool arg1, arg2;
        string oldname, newname;

        for (int index = 0; index < argc; index++) {
            if (index > 1) {
                // if return is std::string::npos, it means not found
                if (string(argv[index]).find("newname=") != std::string::npos) {
                    arg1 = true;
                    newname = string(argv[index]).substr(string("newname=").size());
                }
                if (string(argv[index]).find("oldname=") != std::string::npos) {
                    arg2 = true;
                    oldname = string(argv[index]).substr(string("oldname=").size());
                }
            }
        }

        if (arg1 and arg2) {
            cout << "old name to rename: " << newname << endl;
            cout << "new name to use: " << oldname << endl;
            filesystem::rename(string(presets_folder) + oldname, string(presets_folder) + newname);
        }

    } else {
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
}

void show_current_limit() {
    cout << "Battery Limit Currently in use:\n"
        << first_line(threshold_file)
        << endl;
}
