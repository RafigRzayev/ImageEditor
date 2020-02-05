#include "../include/unit_tests.hpp"
#include "../include/image.hpp"
#include "../include/image_processing.hpp"
#include "../include/helper_functions.hpp"
#include <iostream>

// Returns true if rotation works correctly
bool test_rotation() {

// EXCEPTION TESTS

  // Invalid input image
  Image invalid_mono{5, 3, 4, nullptr};
  Image invalid_mono_copy{5, 3, 4, nullptr};
  rotate_clockwise(invalid_mono);
  if (are_different(invalid_mono, invalid_mono_copy)) {
    return false;
  }  

// FUNCTIONALITY TESTS FOR MONOCHROME IMAGES 

  // Generate 5 x 4 monochrome image
  unsigned char *mono = new unsigned char[20]{
    1,  2,  3,  4,  5,
    6,  7,  8,  9,  10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20     
  };
  Image Mono{5, 4, 1, mono};

  // Generate copy of monochrome image
  unsigned char *mono_2 = new unsigned char[20]{
    1,  2,  3,  4,  5,
    6,  7,  8,  9,  10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20     
  };
  Image Mono_2{5, 4, 1, mono_2};

  // Generate mono image rotated clockwise
  unsigned char *mono_clock = new unsigned char[20]{
    16, 11, 6, 1,
    17, 12, 7, 2,
    18, 13, 8, 3,
    19, 14, 9, 4,
    20, 15, 10, 5
  };
  Image Mono_Clock{4, 5, 1, mono_clock};

  // Generate mono image rotated counter-clockwise
  unsigned char *mono_c_clock = new unsigned char[20]{
    5, 10, 15, 20,
    4, 9, 14, 19, 
    3, 8, 13, 18,
    2, 7, 12, 17,
    1, 6, 11, 16
  };
  Image Mono_C_Clock{4, 5, 1, mono_c_clock};

  // Test 1: Check clockwise rotation
  rotate_clockwise(Mono);
  if (are_different(Mono, Mono_Clock)) {
    return false;
  }

  // Test 2: Rotate 3 more times clockwise, check if it is equal to the original
  rotate_clockwise(Mono);
  rotate_clockwise(Mono);
  rotate_clockwise(Mono);
  if (are_different(Mono, Mono_2)) {
    return false;
  }

  // Test 3: Check counter-clockwise rotation
  rotate_counter_clockwise(Mono);
  if (are_different(Mono, Mono_C_Clock)) {
    return false;
  }

  // Test 4: Rotate 3 more times counter-clockwise, check if it is equal to the original
  rotate_counter_clockwise(Mono);
  rotate_counter_clockwise(Mono);
  rotate_counter_clockwise(Mono);
  if (are_different(Mono, Mono_2)) {
    return false;
  }

// FUNCTIONALITY TESTS FOR RGB IMAGES 

  // Generate 2 x 3 RGB image
  unsigned char *rgb = new unsigned char[18]{
  //R   G   B       R   G   B
    11, 12, 13,     21, 22, 23,
    31, 32, 33,     41, 42, 43,
    51, 52, 53,     61, 62, 63
  };
  Image Rgb{2, 3, 3, rgb};

  // Generate copy of RGB image
  unsigned char *rgb_2 = new unsigned char[18]{
  //R   G   B       R   G   B
    11, 12, 13,     21, 22, 23,
    31, 32, 33,     41, 42, 43,
    51, 52, 53,     61, 62, 63  
  };
  Image Rgb_2{2, 3, 3, rgb_2};

  // Generate RGB image rotated clockwise
  unsigned char *rgb_clock = new unsigned char[18]{
  //R   G   B       R   G   B       R   G   B
    51, 52, 53,     31, 32, 33,     11, 12, 13,
    61, 62, 63,     41, 42, 43,     21, 22, 23
  };
  Image Rgb_Clock{3, 2, 3, rgb_clock};

  // Generate RGB image rotated counter-clockwise
  unsigned char *rgb_c_clock = new unsigned char[18]{
  //R   G   B       R   G   B       R   G   B
    21, 22, 23,     41, 42, 43,     61, 62, 63,
    11, 12, 13,     31, 32, 33,     51, 52, 53
  };
  Image Rgb_C_Clock{3, 2, 3, rgb_c_clock};

  // Test 1: Check clockwise rotation
  rotate_clockwise(Rgb);
  if (are_different(Rgb, Rgb_Clock)) {
    return false;
  }

  // Test 2: Rotate 3 more times clockwise, check if it is equal to the original
  rotate_clockwise(Rgb);
  rotate_clockwise(Rgb);
  rotate_clockwise(Rgb);
  if (are_different(Rgb, Rgb_2)) {
    return false;
  }

  // Test 3: Check counter-clockwise rotation
  rotate_counter_clockwise(Rgb);
  if (are_different(Rgb, Rgb_C_Clock)) {
    return false;
  }

  // Test 4: Rotate 3 more times counter-clockwise, check if it is equal to the original
  rotate_counter_clockwise(Rgb);
  rotate_counter_clockwise(Rgb);
  rotate_counter_clockwise(Rgb);
  if (are_different(Rgb, Rgb_2)) {
    return false;
  }
  
  // All tests have been passed
  return true; 
}
