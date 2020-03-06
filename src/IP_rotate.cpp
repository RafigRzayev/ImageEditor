#include "image_processing.hpp"
#include "logger.hpp"
#include "logs_image_processing.hpp"

// All reversible algorithms change the input image.
// They return boolean representing successfull update

// For list of log messages refer to "logs_image_processing.hpp"
static Logger &logs = Logger::get_instance();

// Reversible algorithm
// Rotates the image in clockwise direction
bool rotate_clockwise(Image &image) {
  if (image.has_exceptions()) {
    logs.add_log(FUNCTIONS[F_ROTATE_CLOCK] + ERRORS[E_INVALID_IMAGE]);
    return false;
  }
  const int NEW_WIDTH{image.get_height()};
  const int NEW_HEIGHT{image.get_width()};
  const int CHANNELS{image.get_channels()};
  const int SIZE{image.get_size()};
  unsigned char *new_data = new unsigned char[SIZE];
  const unsigned char *OLD_DATA = image.get_data();
  const int C1{NEW_HEIGHT * (NEW_WIDTH - 1) * CHANNELS};
  const int C2{NEW_WIDTH * CHANNELS};
  // Algorithm for RGB clockwise rotation
  if (image.is_tricolor()) {
    for (int i{}; i < NEW_HEIGHT; ++i) {
      for (int j{}; j < C2; j += 3) {
        new_data[i * C2 + j] = OLD_DATA[C1 - NEW_HEIGHT * j + CHANNELS * i];
        new_data[i * C2 + j + 1] = OLD_DATA[C1 - NEW_HEIGHT * j + CHANNELS * i + 1];
        new_data[i * C2 + j + 2] = OLD_DATA[C1 - NEW_HEIGHT * j + CHANNELS * i + 2];
      }
    }
  }
  // Algorithm for monochrome clockwise rotation
  else {
    for (int i{}; i < NEW_HEIGHT; ++i) {
      for (int j{}; j < C2; ++j) {
        new_data[i * C2 + j] = OLD_DATA[C1 - NEW_HEIGHT * j + i];
      }
    }
  }
  logs.add_log(FUNCTIONS[F_ROTATE_CLOCK] + ACTIONS[A_ROTATE_CLOCK]);
  image = Image{NEW_WIDTH, NEW_HEIGHT, CHANNELS, new_data};
  return true;
}

// Reversible algorithm
// Rotates the image in counter-clockwise direction
bool rotate_counter_clockwise(Image &image) {
  if (image.has_exceptions()) {
    logs.add_log(FUNCTIONS[F_ROTATE_COUNTER_CLOCK] + ERRORS[E_INVALID_IMAGE]);
    return false;
  }
  const int NEW_WIDTH{image.get_height()};
  const int NEW_HEIGHT{image.get_width()};
  const int CHANNELS{image.get_channels()};
  const int SIZE{image.get_size()};
  unsigned char *new_data = new unsigned char[SIZE];
  const unsigned char *OLD_DATA = image.get_data();
  const int C1{(NEW_HEIGHT - 1) * CHANNELS};
  const int C2{NEW_WIDTH * CHANNELS};
  // Algorithm for RGB counter-clockwise rotation
  if (image.is_tricolor()) {
    for (int i{}; i < NEW_HEIGHT; ++i) {
      for (int j{}; j < C2; j += 3) {
        new_data[i * C2 + j] = OLD_DATA[C1 + NEW_HEIGHT * j - CHANNELS * i];
        new_data[i * C2 + j + 1] = OLD_DATA[C1 + NEW_HEIGHT * j - CHANNELS * i + 1];
        new_data[i * C2 + j + 2] = OLD_DATA[C1 + NEW_HEIGHT * j - CHANNELS * i + 2];
      }
    }
  }
  // Algorithm for monochrome counter-clockwise rotation
  else {
    for (int i{}; i < NEW_HEIGHT; ++i) {
      for (int j{}; j < C2; ++j) {
        new_data[i * C2 + j] = OLD_DATA[C1 + NEW_HEIGHT * j - i];
      }
    }
  }
  logs.add_log(FUNCTIONS[F_ROTATE_COUNTER_CLOCK] + ACTIONS[A_ROTATE_COUNTER_CLOCK]);
  image = Image{NEW_WIDTH, NEW_HEIGHT, CHANNELS, new_data};
  return true;
}