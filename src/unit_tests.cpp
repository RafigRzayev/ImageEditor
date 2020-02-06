#include "../include/unit_tests.hpp"
#include <iostream>

int main() {
    std::cout << "Rotation module: " << (test_rotation() ? "Correct" : "Incorrect") << std::endl;
    std::cout << "Brightness change module: " << (test_change_brightness() ? "Correct" : "Incorrect") << std::endl;
    std::cout << "Monochrome transformation module: " << (test_monochrome() ? "Correct" : "Incorrect") << std::endl;
    std::cout << "Channel extraction module: " << (test_extract_channel() ? "Correct" : "Incorrect") << std::endl;
    return 0;
}