#include <iostream>
#include <memory>
#include <string>

#include "Controller.h"

int main(int argc, char** argv) {

    try {

        unsigned int N = (argc >= 2) ? std::stoi(argv[1]) : 3;

        Controller controller(N);
        std::shared_ptr<Receiver> receiver;

        std::string line;

        do {
            std::getline(std::cin, line);
            if (!line.empty()) {
                controller.parse_command(std::make_unique<TextCommand>(receiver, line));
            }
        } while (line != "EOF");

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
