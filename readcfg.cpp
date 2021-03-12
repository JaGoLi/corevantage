#include "readcfg.h"
#include <iostream>
#include <fstream>
#include <string>

readCfg::readCfg(std::string in_file) {
        this->in_file = in_file;
}

std::string readCfg::shrink_string(std::string input) {
    size_t last_pos = input.find_last_of(' ');
    if (last_pos == input.size() - 1) {
        input = input.substr(0, input.size() - 1);
        return shrink_string(input);
    }
    else {
        return input;
    }
}


void readCfg::get_values() {
    std::fstream curr_file;
    std::string curr_line;
    std::string curr_word;

    curr_file.open(in_file, std::ios::in);

    if (curr_file.is_open() ) {
        int counter = 0;
        while (getline(curr_file, curr_line)) {
            std::string shrunken = shrink_string(curr_line);
            int last_space = shrunken.find_last_of(' ');
            values[counter++] = shrunken.substr(last_space + 1, shrunken.size() - last_space);
            if (values[counter - 1] == "=") {
                values[counter - 1] = "";
            }
        }
    }
    curr_file.close();

}
