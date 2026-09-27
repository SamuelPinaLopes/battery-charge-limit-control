#include "battery_set_functions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

bool check_words(char* word_passed, string expected, bool single_character) { // when you're passing a group of characters, make sure that you'll pass it as pointer, kinda array of characters
    // loop through each character position
    int index = 0;

    // if the size are the same
    if (strlen(word_passed) == expected.length()) {

        while (true) {

            // check each character
            if (word_passed[index] != expected[index]) {
                // the words aren't the same
                return false;
            }
            // when it ends
            if (word_passed[index] == '\0') {
                return true;
            }
            // incrementing characters position
            index++;

        }

    } else {
        return false;
    }

}

void show_settings() {
    /*
     * open the settings file;
     * read each line until finding what you want;
     * show it;
     * close the file
     */
    // openning file with settings on it
    ifstream read_settings("/etc/BatterYLimiT/config.conf");
    string lines;
    // check if the file is open
    if (read_settings.is_open() == true) {
        cout << "Current Settings:\n\n";
        // loop through each line to get the lines with getline method
        while (getline(read_settings, lines)) {
            // print that line
            cout << lines << endl;
        }
        // close the file
        read_settings.close();
        // did fine
    }
}

void save_settings_preset() {
    /* ask for the preset name; done
     * check if it has an extension, if not add it; done
     * check if another file does not have the same name (if has same name, replace that file with this new one); done
     * copy program's config to presets folder; done (important to run as sudo)
     * show if it worked or not; done
     */

    string preset_name;
    string config_file("/etc/BatterYLimiT/config.conf");
    filesystem::path path = "/etc/BatterYLimiT/presets/";

    /* entering preset name */
    cout << "enter preset name: ";
    cin >> preset_name;

    /* checking if preset name has an extension */
    // if word has a size to have an extension
    if (preset_name.length() >= 5) {
        // if word doesn't have extension, add it
        if (preset_name.substr(preset_name.length() - 5, 5) != ".conf") {
            preset_name = preset_name + ".conf";
        }
    // adding extension if is too short to have one
    } else {
        preset_name = preset_name + ".conf";
    }

    /* check if the name is already in use in preset folder */
    // for each file inside preset directory
    for (auto const& entry : filesystem::directory_iterator(path)) {
        // if preset name is already in use
        if ((path.string() + preset_name) == entry.path()) {
            // removing that file
            remove(entry.path().c_str());
        }
    }

    /* creating new preset from config file */
    if (filesystem::copy_file(config_file, path.string() + preset_name)) {
        cout << "preset created!" << endl;
    } else {
        cout << "error creating new preset!" << endl;
    }

}

void set_default_settings() {
    /*
     * loads the config from default config file into .runtime.conf file that "worker program" will read;
     *      open default config file; done
     *      get battery charge battery value; done
     *      open .runtime.conf file; done
     *      write value from default config file into runtime file; done
     *      close those files; done
     *
     *      open config file; done
     *      change its battery charge limit to default; done
     *      write default path to config file on it; done
     *      close file; done
     *
     * tell systemd to reload "worker program";
     *      reload your "worker program" with systemd in background; done
     */
    string line, charge_limit_value, configpath;
    vector <string> array;

    // open default config file
    ifstream defaultconfig("/etc/BatterYLimiT/.default.conf");
    // get charge limit value inside it and save it into line variable
    getline(defaultconfig, line);
    // extract the value from first line
    charge_limit_value = line.substr(line.length()-2, 2);
    // extract default config file path
    while (getline(defaultconfig, line)) {
        if (line.substr(0, 7) == "setting") {
            // get config file path
            configpath = line.substr(8, line.length()-1);
        }
    }
    // close default configuratoin files
    defaultconfig.close();
    // open runtime file and write the value from default config file
    ofstream runtime("/etc/BatterYLimiT/.runtime.conf");
    // write limit value into runtime file
    runtime << charge_limit_value;
    runtime.close();


    // open config file
    ifstream configfile(configpath);
    // load each line into array
    while (getline(configfile, line)) {
        array.push_back(line);
    }
    configfile.close();
    // remove battery charge limit on it
    array[0] = array[0].substr( 0, array[0].length()-2 );
    // remove settings file path on it
    array[1] = array[1].substr(0, 8);
    // add battery charge limit value
    array[0].append(charge_limit_value);
    // add settings file path
    array[1].append(configpath);
    // load each line into file
    ofstream configfile2(configpath);
    for (int index = 0; index < array.size(); index++) {
        configfile2 << array[index] << endl;
    }
    configfile2.close();

    // reload charge limit with "worker program"
    system("systemctl restart setlimit.service");

}

void set_limit() {
    /*
     * ask for the value; done
     * copy value from .runtime file; done
     * write the new limit inside .runtime; done
     * apply the value with "worker program"; done
     * rewrite the old value to .runtime file; done
     * show the value applied; done
     */
    // asking limit value
    int value;
    cout << "new charge limit: ";
    cin >> value;
    // path to runtime file, file containing limit for charge threshold
    std::filesystem::path runtime("/etc/BatterYLimiT/.runtime.conf");
    string line;
    // opens .runtime file
    ifstream runtimefile(runtime);
    // gets settings limit there
    getline(runtimefile, line);
    runtimefile.close();
    // writes the current limit wanted
    ofstream runtimefile2(runtime);
    runtimefile2 << value;
    runtimefile2.close();
    // apply that limit to threshold file
    system("systemctl restart setlimit.service");
    // rewrite settings limit back to file
    ofstream runtimefile3(runtime);
    runtimefile3 << line;
    runtimefile.close();
    // shows new battery charge limit applied
    ifstream currentlimit("/sys/class/power_supply/BAT0/charge_control_end_threshold");
    getline(currentlimit, line);
    cout << "current charge limit: " << line << endl;
    currentlimit.close();

}

void show_presets(std::vector <std::filesystem::path>* array, bool arr) {
    // path to presets folder
    filesystem::path path("/etc/BatterYLimiT/presets/");
    int count = 1;
    if (array == nullptr or arr == false) {
        cout << "presets list: \n";
        // loop through each file inside the presets folder
        for (const auto entry : filesystem::directory_iterator(path)) {
            // formated name of each file
            cout << count
                << " == "
                << string( entry.path() ).substr(
                    string("/etc/BatterYLimiT/presets/").length(),
                    string( entry.path() ).length() - 1
                )
                << endl;
            count++;
        }
    } else {
        for (const std::filesystem::path entry : filesystem::directory_iterator(path)) {
           // add each preset path to array
           array->push_back(entry);
        }
    }

}

void use_preset() {
    /*
     * show all presets avaiable; done
     * ask for what preset name/number to use; done
     * open config file; done
     * write preset path to use inside config file; done
     * close file; done
     * open that preset and .runtime; done
     * write its value to .runtime; done
     * close both files, preset and .runtime; done
     * call worker program to apply that; done
     * show chosen preset name; done
     */
    string selected, line, oldpath, presetpath;
    vector <string> array;
    vector <filesystem::path> presets_array;

    // show all avaiable presets to use
    show_presets();
    // input prest name/number
    cout << "input preset number: ";
    cin >> selected;

    // open config file
    ifstream config("/etc/BatterYLimiT/config.conf");
    // load each line into an array
    while (getline(config, line)) {
        array.push_back(line);
    }
    config.close();

    // get each preset file path
    show_presets(&presets_array, true);

    // loop through each line load into array
    for (int index = 0; index < array.size(); index++) {
        // check if is the line has the setting file path on it
        if (array[index].substr(0, 7) == "setting") {
            // save that old path
            oldpath = array[index].substr(0, 8);
            // remove old path
            array[index] = array[index].substr(0, 8);
            // add new setting file path
            array[index].append(presets_array[stoi(selected)-1]);
            // save preset path
            presetpath = presets_array[stoi(selected)-1];
            break;
        }
    }

    // rewrite all into config
    ofstream config2("/etc/BatterYLimiT/config.conf");
    // loop through each line inside array
    for (int index = 0; index < array.size(); index++) {
        // write each line into config file
        config2 << array[index] << endl;
    }
    config2.close();

    // open preset file
    ifstream file(presetpath);
    // get first line
    getline(file, line);
    // get value from line
    line = line.substr(line.length()-2, line.length()-1);
    file.close();

    // open runtime file
    ofstream runtime("/etc/BatterYLimiT/.runtime.conf");
    // write battery charge limit to it
    runtime << line;
    runtime.close();

    // apply all this through "worker program"
    system("systemctl restart setlimit.service");

    cout << "preset chosen: "
        << presetpath[stoi(selected)-1]
        << endl;
}

void define_limit() {
    /*
     * open config file; done
     * get path to current settings file in use; done
     * close config file; done
     * ask for new limit; done
     * open settings file in use; done
     * write new limit on it; done
     * close file; done
     * show what's inside that file; done
     */
    string line, filepath, newlimit, oldlimit;
    vector <string> array;
    // open config file
    ifstream config("/etc/BatterYLimiT/config.conf");
    if (config.is_open()) {
        while (getline(config, line)) { // loop through each line
            if (line.substr(0, 7) == "setting") { // check if is the correct line
                break;
            }
        }
    }
    config.close();
    // extract just the path to the settings file
    filepath = line.substr(8, line.length()-1);
    // ask for the new limit to insert on it
    cout << "\nsettings currentely using: " << line.substr(string("setting=/etc/BatterYLimiT/").length(), line.length()-1) << endl;
    cout << "insert new battery charge limit: ";
    cin >> newlimit;
    // open settings file
    ifstream settingsfile(filepath);
    if (settingsfile.is_open()) {
        while (getline(settingsfile, line)) { // load each line of the file into an array
            array.push_back(line);
        }
    }
    settingsfile.close();
    // saving old limit
    oldlimit = array[0].substr(array[0].length()-2, array[0].length()-1);
    // remove the old value
    array[0] = array[0].substr(0, array[0].length()-2);
    // add the new value
    array[0].append(newlimit);
    // open settings file again
    ofstream settingsfile2(filepath);
    for (int index = 0; index < array.size(); index++) {
        settingsfile2 << array[index] << endl; // write each line inside the array into the file
    }
    settingsfile2.close();

    // show the full file
    cout << "--------------------------------------\nold limit: " << oldlimit
        << "\nnew limit: " << newlimit
        << "\n\nfull settings:" << endl;
    ifstream settingsfile3(filepath);
    while (getline(settingsfile3, line)) {
        cout << line << endl;
    }
    settingsfile3.close();

}
