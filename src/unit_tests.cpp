#include "../include/unit_tests.hpp"
#include <iostream>
#include "../include/logger.hpp"

int main() {
    std::cout << "Rotation module: " << (test_rotation() ? "Correct" : "Incorrect") << std::endl;
    std::cout << "Brightness change module: " << (test_change_brightness() ? "Correct" : "Incorrect") << std::endl;
    //Logger::get_instance().read_logs();
    return 0;
}