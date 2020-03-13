#include "helper_functions.hpp"
#include "image.hpp"
#include "image_processing.hpp"
#include "unit_tests.hpp"
#include <iostream>

// Returns true if quantization works correctly
bool test_quantize() {

// EXCEPTION TESTS

  // Case 1: Input image is invalid
  Image empty_img{};
  Image *ptr = quantize(empty_img, 5);
  if(ptr != nullptr) {
    delete ptr;
    return false;
  }

  // Case 2: Quantization level above 256
  const size_t DATA_SIZE_{4};
  unsigned char *data_ = new unsigned char[DATA_SIZE_]{0, 32, 64, 128};
  Image IMG_{2, 2, 1, data_};
  ptr = quantize(IMG_, 257);
  if(ptr != nullptr) {
    delete ptr;
    return false;
  }
  
  // Case 3: Quantization level below 2
  ptr = quantize(IMG_, 1);
  if(ptr != nullptr) {
    delete ptr;
    return false;
  }

// FUNCTIONALITY TESTS

  // Create original image
  const int WIDTH{7}, HEIGHT{1}, CHANNELS{1};
  unsigned char *data = new unsigned char[WIDTH * HEIGHT * CHANNELS]{0, 38, 126, 127, 128, 191, 255};
  const Image IMG{WIDTH, HEIGHT, CHANNELS, data};

  // Create reference image with quantization level 2
  unsigned char *data_2 = new unsigned char[WIDTH * HEIGHT * CHANNELS]{0, 0, 0, 0, 255, 255, 255};
  const Image IMG_REF_L2{WIDTH, HEIGHT, CHANNELS, data_2};

  // Create reference image with quantization level 3
  unsigned char *data_3 = new unsigned char[WIDTH * HEIGHT * CHANNELS]{0, 0, 127, 127, 127, 127, 255};
  const Image IMG_REF_L3{WIDTH, HEIGHT, CHANNELS, data_3};

  // Create reference image with quantization level 4
  unsigned char *data_4 = new unsigned char[WIDTH * HEIGHT * CHANNELS]{0, 0, 85, 85, 170, 170, 255};
  const Image IMG_REF_L4{WIDTH, HEIGHT, CHANNELS, data_4};

  // Combine pointers to reference images
  const size_t IMAGE_COUNT{4};
  const Image* REF_IMAGES[IMAGE_COUNT]{&IMG, &IMG_REF_L2, &IMG_REF_L3, &IMG_REF_L4};

  // Generate images. Memory must be deallocated manually.
  Image *images[IMAGE_COUNT]{quantize(IMG, 256),  quantize(IMG, 2), quantize(IMG, 3), quantize(IMG, 4)};
  
  // Check for exceptions
  for(size_t i{0}; i < IMAGE_COUNT; ++i) {
      if(images[i] == nullptr) {
          free_img_ptr_sequence(images, IMAGE_COUNT);
          return false;
      }
  }

  // Compare generated and reference images
  for(size_t i{0}; i < IMAGE_COUNT; ++i) {
      if(are_different(*images[i], *REF_IMAGES[i])) {
          free_img_ptr_sequence(images, IMAGE_COUNT);
          return false;
      }
  }

  // All tests have been passed
  free_img_ptr_sequence(images, IMAGE_COUNT);
  return true;
}
