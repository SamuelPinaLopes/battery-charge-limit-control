#include <iostream>
#include <string>
#include <filesystem>
#include "../src/utilities.h"

std::filesystem::path config_file("/etc/BatterYLimiT/config.conf");

int main(int argc, char **argv) {
   
   if (argc > 1) {
      std::string word(argv[1]);
      std::cout << find_line(word, config_file).value_or("I didn't find it...") << std::endl;
   
   } else {
      std::cout << "no parameters passed!" << std::endl;
   
   }

   return 0;
   
}
