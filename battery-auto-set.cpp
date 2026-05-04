#include <iostream>
#include <filesystem>
#include <vector>


using namespace std;


vector<string> get_directories(filesystem::path defaultPath) { // default path to look
    vector<string> all; // array of all directories inside default path

    filesystem::directory_iterator it(defaultPath); // starting the DIRECTORY_iterator and giving its start point
    filesystem::directory_iterator end;// ending the DIRECTORY_iterator and it has nothing, end == '' so you don't have to pass nothing.

    for (; it != end; ++it) { // loop through the directory_iterator
        filesystem::directory_entry entry = *it; // entry is like a variable that recives the value that it is pointing

        if (entry.is_directory()) { // if is really a directory
            all.push_back(entry.path().filename().string()); // adding all directories inside array to return
        }
    }

    return all; // returning the folders found inside power_supply
}


string power_supply("/sys/class/power_supply/");


int main() {

    vector<string> directories(get_directories(power_supply)); // creating a vector with return of directories function

    vector<string>::iterator it; // iterator for indexing elements of directories array

    for (it = directories.begin(); it != directories.end(); ++it) { // loop through each folder inside the poewr_supply directory
        
        if ((*it).compare(0, 2, "BA") == 0) { // know the correct folder, add another cases, for other laptops, pc, etc.
            cout << "all things right!\nbecause: " << *it << endl; // if it is the correct folder
        }
    
    }

    return 0;
}