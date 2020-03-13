#include "helper_functions.hpp"
#include "image.hpp"
#include "image_processing.hpp"
#include "unit_tests.hpp"
#include <iostream>

// Returns true if monochrome transformation works correctly
bool test_monochrome() {

// EXCEPTION TESTS

  // Case 1: Input image is invalid
  const Image EMPTY_IMG_{};
  Image *ptr = monochrome(EMPTY_IMG_);
  if (ptr != nullptr) {
    delete ptr;
    return false;
  }

  // Case 2: Input image not tricolor
  const size_t WIDTH_{2}, HEIGHT_{2}, MONO_CHANNELS_{1};
  unsigned char *data_mono_ = new unsigned char[WIDTH_ * HEIGHT_ * MONO_CHANNELS_]{1, 2, 3, 4};
  const Image MONO_{WIDTH_, HEIGHT_, MONO_CHANNELS_, data_mono_};
  ptr = monochrome(MONO_);
  if (ptr != nullptr) {
    delete ptr;
    return false;
  }

// FUNCTIONALITY TESTS

  // Generate 2 x 3 RGB image
  const size_t WIDTH{2}, HEIGHT{3}, RGB_CHANNELS{3};
  unsigned char *data_rgb = new unsigned char[WIDTH * HEIGHT * RGB_CHANNELS]{
  //R   G   B       R   G   B
    0, 50, 100,     0, 100, 50,
    50, 0, 100,     50, 100, 0,
    100, 0, 50,     100, 50, 0
  };
  const Image RGB{WIDTH, HEIGHT, RGB_CHANNELS, data_rgb};

  // Generate reference MONO image with R_COEF{0.2990}, G_COEF{0.5870}, B_COEF{0.1140};
  const size_t MONO_CHANNELS{1};
  unsigned char *data_mono = new unsigned char[WIDTH * HEIGHT * MONO_CHANNELS]{
    40, 64,
    26, 73,
    35, 59
  };
  const Image MONO_REF{WIDTH, HEIGHT, MONO_CHANNELS, data_mono};

  // Generate mono image. Check for exceptions
  Image *mono = monochrome(RGB);
  if (mono == nullptr) {
    return false;
  }

  // Compare generated monochrome with reference monochrome
  if (are_different(*mono, MONO_REF)) {
    delete mono;
    return false;
  }

  // All tests have been passed
  delete mono;
  return true;
}
