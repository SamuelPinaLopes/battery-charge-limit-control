#include <iostream>
#include <string>
#include <filesystem>
#include "../src/utilities.h"
#include <vector>


using namespace std;

filesystem::path presets_folder("/etc/BatterYLimiT/presets/");



int main(int argc, char **argv) {
    
    vector<filesystem::path> array;

    file_path(&array, presets_folder);

    for (int index = 0; index < array.size(); index++) {
        cout << array[index] << endl;
    }


    return 0;

}
