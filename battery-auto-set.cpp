#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>


using namespace std;


vector<filesystem::path> get_directories(filesystem::path defaultPath) { // default path to look
    vector<filesystem::path> all; // array of all directories inside default path

    filesystem::directory_iterator it(defaultPath); // starting the DIRECTORY_iterator and giving its start point
    filesystem::directory_iterator end;// ending the DIRECTORY_iterator and it has nothing, end == '' so you don't have to pass nothing.

    for (; it != end; ++it) { // loop through the directory_iterator
        filesystem::directory_entry entry = *it; // entry is like a variable that recives the value that it is pointing

        if (entry.is_directory()) { // if is really a directory
            all.push_back(entry.path().filename()); // adding all directories inside array to return
        }
    }

    return all;
}


string power_supply_info("/sys/class/power_supply/");


int main() {

    vector<filesystem::path> directories(get_directories(power_supply_info)); // creating a vector with return of directories function

    vector<filesystem::path>::iterator it; // iterator for indexing elements of directories array

    for (it = directories.begin(); it != directories.end(); ++it) { // loop through
        cout << "directory: " << *it << endl;
    }

    return 0;
}