#pragma once 

#include "image.hpp"

// Function to print memory value in Bytes, MB, GB and etc.
void print_memory(unsigned long long BYTE_VAL);

// Returns true if images are different
bool are_different(const Image &IM1, const Image &IM2);

// Deallocates memory from sequence of image pointers
void free_img_ptr_sequence(Image **img_ptr_sequence, const size_t SIZE);