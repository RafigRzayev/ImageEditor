#include "helper_functions.hpp"

#include <iomanip>
#include <iostream>

// Function to print memory value in Bytes, MB, GB and etc.
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

// Returns true if images are different
bool are_different(const Image &IM1, const Image &IM2) {

  // Compare channels
  if (IM1.get_channels() != IM2.get_channels()) {
    return true;
  }
  // Compare heights
  if (IM1.get_height() != IM2.get_height()) {
    return true;
  }
  // Compare widths
  if (IM1.get_width() != IM2.get_width()) {
    return true;
  }
  // Compare pixel count
  if (IM1.get_size() != IM2.get_size()) {
    return true;
  }
  // Compare data
  // case 1: both are empty -> images are same
  if (IM1.is_empty() && IM2.is_empty()) {
    return false;
  }
  // case 2: one is empty -> images are different
  if (IM1.is_empty() || IM2.is_empty()) {
    return true;
  }
  // case 3: both have data -> compare data
  const int PIXEL_COUNT{IM1.get_size()};
  const unsigned char *data1 = IM1.get_data();
  const unsigned char *data2 = IM2.get_data();
  for (int i{0}; i < PIXEL_COUNT; ++i) {
    if (data1[i] != data2[i]) {
      return true;
    }
  }
  return false;  // No difference found, images are same
}

// Deallocates memory from sequence of image pointers
void free_img_ptr_sequence(Image **img_ptr_sequence, const size_t SIZE) {
  Image **begin = img_ptr_sequence;
  Image **const end = img_ptr_sequence + SIZE;
  while (begin != end) {
    if(begin != nullptr){
        delete *begin;
    }
    ++begin;
  }
}