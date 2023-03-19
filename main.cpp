#include "CulLang.h"

int main() {


    // class for handling the language work
    CulLang::CulLang lang;

    //getting the filename to compile
    std::string file;
    std::cout << "Enter filename:\n";
    std::cin >> file;

    lang.runFile(file);


    return 0;
}
