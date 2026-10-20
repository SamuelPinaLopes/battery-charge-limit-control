#include <iostream>
#include <string>
#include <filesystem>
#include "../src/utilities.h"

std::filesystem::path config_file("/etc/BatterYLimiT/config.conf"),
write("/tmp/file.txt");

int main(int argc, char **argv) {

    if (argc > 1) {
        std::string word(argv[1]);


        std::cout << find_line(word, config_file).value_or("I didn't find it...") << std::endl;

        std::string charge_limit, line;
        std::optional <std::string> settings_path;

        settings_path = find_line(word, config_file);

        if (settings_path.has_value()) {
            *settings_path = settings_path->substr(8);
        } else {
            std::cout << "find_line function didn't find the word" << std::endl;

        }

        charge_limit = first_line(settings_path.value_or(config_file));
        
        write_line(
            charge_limit.substr( charge_limit.length()-2 ), write
        );

   } else {
        std::cout << "no parameters passed!" << std::endl;

   }

    return 0;

}
