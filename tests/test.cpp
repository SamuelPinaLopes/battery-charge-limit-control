#include <iostream>
#include <string>
#include <filesystem>
#include "../src/utilities.h"

std::filesystem::path config_file("/etc/BatterYLimiT/config.conf");

int main() {
   
   std::string word("setting");

   std::cout << find_line(word, config_file) << std::endl;

   return 0;
   
}
