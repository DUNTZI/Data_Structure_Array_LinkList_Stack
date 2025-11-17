#include "Utils.hpp"
#include <iostream>
#include <string>
#include <limits> // For numeric_limits

void pauseSystem() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(std::cin.rdbuf()->in_avail() > 0) {
         std::cin.get();
    }
    std::cin.get();
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (std::cin.peek() == '\n') {
            } else {
                std::cout << "Invalid input. Please enter a number only.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}