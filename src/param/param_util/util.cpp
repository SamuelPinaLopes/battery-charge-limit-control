#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

void show_file(std::filesystem::path file) {
    std::ifstream somefile(file);
    std::string line;

    if (somefile.is_open()) {
        while (std::getline(somefile, line)) {
            std::cout << line << std::endl;
        }
    }

    somefile.close();
}
