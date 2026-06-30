#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    cout << "this is what were inside argv: ";

    for (int number = 0; number < argc; number++) {
        if (number != 0) {
            cout << argv[number] << " ";
        }
    }
    
    return 0;
}