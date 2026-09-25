#include <iostream>
#include "battery_set_functions.h"
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

bool check_words(char* word_passed, string expected, bool single_character) { // when you're passing a group of characters, make sure that you'll pass it as *, kinda array of characters
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
     * loads the config from config file into .runtime.conf file that "worker program" will read;
     *      open config file; done
     *      get battery charge battery value; done
     *      open .runtime.conf file; done
     *      write the value inside config file; done
     *      close those files; done
     *
     * tell systemd to reload "worker program";
     *      reload your "worker program" with systemd in background; done
     */
    // open default config file
    string line, charge_limit_value;
    ifstream config_file("/etc/BatterYLimiT/.default.conf");
    // get charge limit value inside it and save it into line variable
    while (getline(config_file, line)) {
        if (line.length() > 2) {
            charge_limit_value = line.substr(line.length() - 2, 2);
        }
    }
    // close default configuratoin file
    config_file.close();
    // open runtime file and write the value from default config file
    ofstream runtime("/etc/BatterYLimiT/.runtime.conf");
    runtime << charge_limit_value;
    runtime.close();
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

void show_presets() {
    cout << "presets list: \n";
    // path to presets folder
    filesystem::path path("/etc/BatterYLimiT/presets/");
    int count = 1;
    // loop through each file inside the presets folder
    for (const auto entry : filesystem::directory_iterator(path)) {
        // formated name of each file
        cout << count
             << " == "
             << string( entry.path() ).substr(26, string( entry.path() ).length() - 1)
             << endl;
        count++;
    }
}

void define_limit() {cout << "define charge limit to current setting/preset" << endl;}
void rename_preset(string preset) {cout << "renaming preset: " << preset << endl;}
void use_preset(int index, string name) {cout << "preset choosen: " << name << endl;}

/*
 #include <iostream>
 #include <filesystem>
 #include <cstdlib>
 #include <string>

 namespace fs = std::filesystem;

 bool copy_to_system_directory(const fs::path& source, const fs::path& system_destination) {
     std::error_code ec;

     // Step 1: Copy file to /tmp using std::filesystem
     fs::path temp_path = fs::temp_directory_path() / source.filename();

     fs::copy_file(source, temp_path, fs::copy_options::overwrite_existing, ec); // important to learn more about filesystem options thing, I didn't know you have specific option for copying files and overwrite exiting was one of them.
     if (ec) {
         std::cerr << "Failed to copy to temp directory: " << ec.message() << "\n";
         return false;
     }

     // Step 2: Move the file from /tmp to the system folder using root privileges
     // Command built: pkexec mv /tmp/your_file.conf /etc/your_file.conf
     std::string command = "pkexec mv " + temp_path.string() + " " + system_destination.string();

     int result = std::system(command.c_str());

     return (result == 0);
 }

 int main() {
     fs::path my_file = "app.conf";
     fs::path target = "/etc/app.conf";

     if (copy_to_system_directory(my_file, target)) {
         std::cout << "Successfully copied file to system path!\n";
     } else {
         std::cerr << "Operation failed or canceled by user.\n";
     }

     return 0;
 }
 */
