#include "../include/helper_functions.hpp"
#include "../include/image.hpp"
#include "../include/image_processing.hpp"
#include "../include/unit_tests.hpp"
#include <iostream>

// Returns true if channel extraction works correctly
bool test_extract_channel() {

// EXCEPTION TESTS

  // Case 1: Input image is invalid
  const Image EMPTY_IMG_{};
  Image *ptr = extract_BLUE(EMPTY_IMG_);
  if (ptr != nullptr) {
    delete ptr;
    return false;
  }

  // Case 2: Input image not tricolor
  const size_t WIDTH_{2}, HEIGHT_{2}, MONO_CHANNELS_{1};
  unsigned char *data_mono_ = new unsigned char[WIDTH_ * HEIGHT_ * MONO_CHANNELS_]{1, 2, 3, 4};
  const Image MONO_{WIDTH_, HEIGHT_, MONO_CHANNELS_, data_mono_};
  ptr = extract_RED(MONO_);
  if (ptr != nullptr) {
    delete ptr;
    return false;
  }

// FUNCTIONALITY TESTS

  // Create 2 x 3 RGB image
  const size_t WIDTH{2}, HEIGHT{3}, RGB_CHANNELS{3};  
  unsigned char *data_rgb = new unsigned char[WIDTH * HEIGHT * RGB_CHANNELS]{
  //R   G   B       R   G   B
    11, 12, 13,     21, 22, 23,
    31, 32, 33,     41, 42, 43,
    51, 52, 53,     61, 62, 63
  };
  const Image RGB{WIDTH, HEIGHT, RGB_CHANNELS, data_rgb};

  // Create reference RED image
  const size_t RED_CHANNELS{1}, GREEN_CHANNELS{1}, BLUE_CHANNELS{1};
  unsigned char *data_red = new unsigned char[WIDTH * HEIGHT * RED_CHANNELS]{
    11, 21, 
    31, 41, 
    51, 61
  };
  const Image RED_REF{WIDTH, HEIGHT, RED_CHANNELS, data_red};

  // Create reference GREEN image
  unsigned char *data_green = new unsigned char[WIDTH * HEIGHT * GREEN_CHANNELS]{
    12, 22, 
    32, 42, 
    52, 62
  };
  const Image GREEN_REF{WIDTH, HEIGHT, GREEN_CHANNELS, data_green}; 

  // Create reference BLUE image
  unsigned char *data_blue = new unsigned char[WIDTH * HEIGHT * BLUE_CHANNELS]{
    13, 23, 
    33, 43, 
    53, 63
  };
  const Image BLUE_REF{WIDTH, HEIGHT, BLUE_CHANNELS, data_blue};  

  // Generate images. Memory must be deallocated manually.
  Image *red = extract_RED(RGB);
  Image *green = extract_GREEN(RGB);
  Image *blue = extract_BLUE(RGB);

  // Put them into array to use free_img_ptr_sequence() 
  const size_t IMAGE_COUNT{3};
  Image *images[IMAGE_COUNT]{red, green, blue};

  // Check for exceptions.
  if(red == nullptr || green == nullptr || blue == nullptr) {
      free_img_ptr_sequence(images, IMAGE_COUNT);
      return false;
  }

  // Compare generated and reference images
  if(are_different(*red, RED_REF) || are_different(*green, GREEN_REF) || are_different(*blue, BLUE_REF)) {
      free_img_ptr_sequence(images, IMAGE_COUNT);
      return false;
  }

  // All tests have been passed
  free_img_ptr_sequence(images, IMAGE_COUNT);
  return true;
}