#include "../include/print_memory.hpp"

#include <iomanip>
#include <iostream>

// Helper function to print memory value in Bytes, MB, GB and etc.
void print_memory(unsigned long long BYTE_VAL) {
const double kB {1000}, MB{1000*1000}, GB{1000*1000*1000};
if(BYTE_VAL == 0) {
    std::cout << "0\n";
    return;
}
if(BYTE_VAL < kB) {
    std::cout << BYTE_VAL << (BYTE_VAL == 1 ? " Byte\n" : " Bytes\n");
    return;
}
if(BYTE_VAL < MB) {
    std::cout << std::setprecision(1) << std::fixed << BYTE_VAL/kB << " kB (" << BYTE_VAL << " Bytes)\n";
    return;
}
if(BYTE_VAL < GB) {
    std::cout << std::setprecision(1) << std::fixed << BYTE_VAL/MB << " MB (" << BYTE_VAL << " Bytes)\n";
    return;
}
std::cout << std::setprecision(1) << std::fixed << BYTE_VAL/GB << " GB\n";
}