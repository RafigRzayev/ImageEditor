#include "image_processing.hpp"
#include "logger.hpp"
#include "logs_image_processing.hpp"

// All non-reversible algorithms return pointer to generated image or nullptr on failure.
// Input image is never changed.
// It is user's responsibility to free memory of new image

// For list of log messages refer to "logs_image_processing.hpp"
static Logger &logs = Logger::get_instance();

// Non-reversible algorithm.
// Changes brightness of an image.
// Range of change values: [-255, 255]
Image *change_brightness(const Image &IMAGE, const int CHANGE_VAL) {
  // Case 1: Invalid input
  if (IMAGE.has_exceptions()) {
    logs.add_log(FUNCTIONS[F_CHANGE_BRIGHTNESS] + ERRORS[E_INVALID_IMAGE]);
    return nullptr;
  }
  // Case 2: Change value out of range
  if (CHANGE_VAL < -255 || CHANGE_VAL > 255) {
    logs.add_log(FUNCTIONS[F_CHANGE_BRIGHTNESS] + ERRORS[E_BRIGHTNESS_CHANGE_VALUE]);
    return nullptr;
  }
  // Case 3: No change
  if (CHANGE_VAL == 0) {
    logs.add_log(FUNCTIONS[F_CHANGE_BRIGHTNESS] + ACTIONS[A_NO_BRIGHTNESS_CHANGE]);
    return new Image{IMAGE};
  }
  const int SIZE{IMAGE.get_size()};
  unsigned char *new_data = new unsigned char[SIZE];
  const unsigned char *OLD_DATA = IMAGE.get_data();
  // Algorithm
  if (CHANGE_VAL > 0) { 
    // Case 4: Increase brightness - ceiling 255
    for (int i{0}; i < SIZE; ++i) {
      int temp = OLD_DATA[i] + CHANGE_VAL;
      new_data[i] = static_cast<unsigned char>(temp < 255 ? temp : 255);
    }
  } else 
  {
    // Case 5: Decrease brightness - floor 0
    for (int i{0}; i < SIZE; ++i) {
      int temp = OLD_DATA[i] + CHANGE_VAL;
      new_data[i] = static_cast<unsigned char>(temp > 0 ? temp : 0);
    }
  }
  logs.add_log(FUNCTIONS[F_CHANGE_BRIGHTNESS] + ACTIONS[A_CHANGE_BRIGHTNESS]);
  return new Image{IMAGE.get_width(), IMAGE.get_height(), IMAGE.get_channels(), new_data};
}