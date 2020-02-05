#include "../include/helper_functions.hpp"
#include "../include/image.hpp"
#include "../include/image_processing.hpp"
#include "../include/unit_tests.hpp"
#include <iostream>

// Returns true if brightness change function works correctly
bool test_change_brightness() {

// FUNCTIONALITY TESTS

  // Generate original image
  const int WIDTH{5}, HEIGHT{1}, CHANNELS{1}, COUNT{WIDTH * HEIGHT * CHANNELS};
  unsigned char *DATA = new unsigned char[COUNT]{0, 1, 128, 254, 255};
  const Image IMG{WIDTH, HEIGHT, CHANNELS, DATA};

  // brightness decreased by 255 (black)
  unsigned char *DATA_MINUS_255 = new unsigned char[COUNT]{0, 0, 0, 0, 0};
  const Image IMG_MINUS_255{WIDTH, HEIGHT, CHANNELS, DATA_MINUS_255};

  // brightness increaed by 255 (white)
  unsigned char *DATA_PLUS_255 = new unsigned char[COUNT]{255, 255, 255, 255, 255};
  const Image IMG_PLUS_255{WIDTH, HEIGHT, CHANNELS, DATA_PLUS_255};

  // brightness decreased by 2
  unsigned char *DATA_MINUS_2 = new unsigned char[COUNT]{0, 0, 126, 252, 253};
  const Image IMG_MINUS_2{WIDTH, HEIGHT, CHANNELS, DATA_MINUS_2};

  // brightness increased by 2
  unsigned char *DATA_PLUS_2 = new unsigned char[COUNT]{2, 3, 130, 255, 255};
  const Image IMG_PLUS_2{WIDTH, HEIGHT, CHANNELS, DATA_PLUS_2};

  // Array of pointers to reference images. 
  // Images will be destroyed automatically at the end of scope. 
  const size_t TEST_COUNT{5};
  const Image *REF_IMAGES[TEST_COUNT]{&IMG, &IMG_MINUS_255, &IMG_PLUS_255, &IMG_MINUS_2, &IMG_PLUS_2};

  // Array of pointers to images created by change_brightness().
  // Memory must be freed manually
  Image *images[TEST_COUNT]{
      change_brightness(IMG, 0), change_brightness(IMG, -255),
      change_brightness(IMG, 255), change_brightness(IMG, -2),
      change_brightness(IMG, 2)};

  // Check if exceptions occured during change_brightness()
  for (size_t i{0}; i < TEST_COUNT; ++i) {
    if (images[i] == nullptr) {
      free_img_ptr_sequence(images, TEST_COUNT);
      return false;
    }
  }

  // Compare with references
  for (size_t i{0}; i < TEST_COUNT; ++i) {
    if (are_different(*images[i], *REF_IMAGES[i])) {
      free_img_ptr_sequence(images, TEST_COUNT);
      return false;
    }
  }

  // Passed functionality tests
  free_img_ptr_sequence(images, TEST_COUNT);

// EXCEPTION TESTS

  // Case 1: Input image is invalid
  Image empty_img{};
  Image *ptr = change_brightness(empty_img, 200);
  if(ptr != nullptr) {
    delete ptr;
    return false;
  }

  // Case 2: Change value above 255
  ptr = change_brightness(IMG, 256);
  if(ptr != nullptr) {
    delete ptr;
    return false;
  }
  
  // Case 3: Change value below -255
  ptr = change_brightness(IMG, -256);
  if(ptr != nullptr) {
    delete ptr;
    return false;
  }

  // All tests have been passed
  return true;
}