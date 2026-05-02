#include <iostream>
#include <filesystem>


using namespace std;


void get_directories() {
    filesystem::path way = "/sys/class/power_supply/";

    filesystem::directory_iterator it(way);
    filesystem::directory_iterator end;

    for (; it != end; ++it) {
        filesystem::directory_entry entry = *it;

        if (entry.is_directory()) {
            cout << "Directories: " << entry.path().filename() << endl;
        }
    }
}

int main() {

    get_directories();

    return 0;
}