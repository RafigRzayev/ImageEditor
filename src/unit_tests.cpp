#include "../include/unit_tests.hpp"
#include <iostream>

int main() {
    std::cout << "Rotation module: " << (test_rotation() ? "Correct" : "Incorrect") << std::endl;
    return 0;
}