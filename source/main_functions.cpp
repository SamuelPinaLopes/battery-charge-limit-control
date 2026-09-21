#include <fstream>
#include <filesystem>

// path to battery charge threshold
std::filesystem::path threshold("/sys/class/power_supply/BAT0/charge_control_end_thresholdtxt");
// path to runtime file, file containing limit for charge threshold
std::filesystem::path runtime("/etc/BatterYLimiT/.runtime.conf");

// function to first line of any file
std::string get_value(std::filesystem::path file) {
    // open file for reading
    std::fstream somefile( file , std::ios::in);
    std::string line; // variable to store the first line

    std::getline( somefile, line ); // get the first line

    somefile.close(); // close the file
    return line; // return the value
}

// function to write the limit to charge threshold file
void write_limit() {
    // check if threshold and runtime charge limit value aren't matching
    if (get_value(threshold) != get_value(runtime)) {
        // open treshold file for writing
        std::fstream threshold_file( threshold, std::ios::out );
        // makes sure the file is open
        if (threshold_file.is_open()) {
            // write charge limit value into threshold file
            threshold_file << get_value( runtime );
        }
        // closing the file
        threshold_file.close();
    }
}
