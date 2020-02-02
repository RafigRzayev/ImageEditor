#include "../include/image_processing.hpp"
#include "../include/logger.hpp"
#include "../include/logs_image_processing.hpp"

// All non-reversible algorithms return pointer to generated image or nullptr on
// failure. Input image is never changed. It is user's responsibility to free
// memory of new image

// For list of log messages refer to "logs_image_processing.hpp"
static Logger &logs = Logger::get_instance();

// Generates histogram of monochrome image. Non-reversible algorithm
Image *histogram_BW(const Image &IMAGE) {
  // Exceptions
  if(IMAGE.has_exceptions()) {
      logs.add_log(FUNCTIONS[F_HISTOGRAM] + ERRORS[E_INVALID_IMAGE]);
      return nullptr;
  }
  if(!IMAGE.is_monocolor()) {
      logs.add_log(FUNCTIONS[F_HISTOGRAM] + ERRORS[E_IMAGE_NOT_MONOCHROME]);
      return nullptr;
  }
  // Variables to build the image
  const int H_WIDTH{256}, H_HEIGHT{256}, H_CHANNELS{IMAGE.get_channels()};
  const int HISTOGRAM_SIZE{H_WIDTH * H_HEIGHT * H_CHANNELS};
  const int IMAGE_SIZE{IMAGE.get_size()};
  unsigned char *new_data = new unsigned char[HISTOGRAM_SIZE];
  const unsigned char *OLD_DATA = IMAGE.get_data();
  // Histogram calculation
  const int NUMBER_OF_COLORS{256};
  int histogram[NUMBER_OF_COLORS]{};
  for (int i{0}; i < IMAGE_SIZE; ++i) {
    ++histogram[OLD_DATA[i]];
  }
  // Find maximum inside histogram
  int max{};
  for (int i{0}; i < NUMBER_OF_COLORS; ++i) {
    if (histogram[i] > max) {
      max = histogram[i];
    }
  }
  // Scale all histogram values according to max:
  // Result: Range of histogram becomes [0, 1] instead of [0, max]
  // Then multiply values by (H_HEIGHT - 1) so that max fits whole Y axis:
  const float max_ = max;
  for (int i{0}; i < NUMBER_OF_COLORS; ++i) {
    histogram[i] = (histogram[i] / max_) * (H_HEIGHT - 1);
  }
  // Fill image with background color
  const int BACKGROUND_COLOR{20};
  for (int i{0}; i < HISTOGRAM_SIZE; ++i) {
    new_data[i] = BACKGROUND_COLOR;
  }
  // Update each column until height reaches histogram value
  const int WHITE{255};
  for (int i{0}; i < H_WIDTH; ++i) {
    for (int j{H_HEIGHT - histogram[i]}; j < H_HEIGHT; ++j) {
      new_data[j * H_WIDTH + i] = WHITE;
    }
  }
  logs.add_log(FUNCTIONS[F_HISTOGRAM] + ACTIONS[A_HISTOGRAM]);
  return new Image{H_WIDTH, H_HEIGHT, H_CHANNELS, new_data};
}

// Generates histogram of RGB image. Non-reversible algorithm
Image *histogram_RGB(const Image &IMAGE) {
  // Exceptions
  if(IMAGE.has_exceptions()) {
      logs.add_log(FUNCTIONS[F_HISTOGRAM] + ERRORS[E_INVALID_IMAGE]);
      return nullptr;
  }
  if(!IMAGE.is_tricolor()) {
      logs.add_log(FUNCTIONS[F_HISTOGRAM] + ERRORS[E_IMAGE_NOT_RGB]);
      return nullptr;
  }
  // Variables to build the image
  const int H_WIDTH{256}, H_HEIGHT{128}, H_CHANNELS{IMAGE.get_channels()};
  const int HISTOGRAM_SIZE{H_WIDTH * H_HEIGHT * H_CHANNELS};
  const int IMAGE_SIZE{IMAGE.get_size()};
  unsigned char *new_data = new unsigned char[HISTOGRAM_SIZE];
  const unsigned char *OLD_DATA = IMAGE.get_data();
  // Histogram calculation
  const int NUMBER_OF_COLORS{256};
  int histogram_R[NUMBER_OF_COLORS]{};
  int histogram_G[NUMBER_OF_COLORS]{};
  int histogram_B[NUMBER_OF_COLORS]{};
  for (int i{0}; i < IMAGE_SIZE; i += 3) {
    ++histogram_R[OLD_DATA[i]];
    ++histogram_G[OLD_DATA[i + 1]];
    ++histogram_B[OLD_DATA[i + 2]];
  }
  // Find maximum inside histogram
  int max{};
  for (int i{0}; i < NUMBER_OF_COLORS; ++i) {
    if (histogram_R[i] > max) {
      max = histogram_R[i];
    }
    if (histogram_G[i] > max) {
      max = histogram_G[i];
    }
    if (histogram_B[i] > max) {
      max = histogram_B[i];
    }
  }
  // Scale all histogram values according to max:
  // Result: Range of histogram becomes [0, 1] instead of [0, max]
  // Then multiply values by (H_HEIGHT - 1) so that max fits whole Y axis:
  const float max_ = max;
  for (int i{0}; i < NUMBER_OF_COLORS; ++i) {
    histogram_R[i] = (histogram_R[i] / max_) * (H_HEIGHT - 1);
    histogram_G[i] = (histogram_G[i] / max_) * (H_HEIGHT - 1);
    histogram_B[i] = (histogram_B[i] / max_) * (H_HEIGHT - 1);
  }
  // Fill image with background color
  const int BACKGROUND_COLOR{20};
  for (int i{0}; i < HISTOGRAM_SIZE; ++i) {
    new_data[i] = BACKGROUND_COLOR;
  }
  // Update each column until height reaches histogram value
  const int WHITE{255};
  for (int i{0}; i < H_WIDTH; ++i) {
    for (int j{H_HEIGHT - histogram_R[i]}; j < H_HEIGHT; ++j) {
      new_data[j * H_WIDTH * 3 + 3 * i] = WHITE;
    }
    for (int j{H_HEIGHT - histogram_G[i]}; j < H_HEIGHT; ++j) {
      new_data[j * H_WIDTH * 3 + 3 * i + 1] = WHITE;
    }
    for (int j{H_HEIGHT - histogram_B[i]}; j < H_HEIGHT; ++j) {
      new_data[j * H_WIDTH * 3 + 3 * i + 2] = WHITE;
    }
  }
  logs.add_log(FUNCTIONS[F_HISTOGRAM] + ACTIONS[A_HISTOGRAM]);
  return new Image{H_WIDTH, H_HEIGHT, H_CHANNELS, new_data};
}

// Generates histogram of the image
Image *histogram(const Image &IMAGE) {
    return (IMAGE.is_monocolor() ? histogram_BW(IMAGE) : histogram_RGB(IMAGE));
}

