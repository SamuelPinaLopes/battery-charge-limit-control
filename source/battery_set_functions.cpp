#include <string>
#include <cstring>

using namespace std;

bool check_words(char* word_passed, string expected, bool single=false) { // when you're passing a group of characters, make sure that you'll pass it as *, kinda array of characters    
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