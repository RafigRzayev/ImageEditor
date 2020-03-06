#include "image_processing.hpp"
#include "logger.hpp"
#include "logs_image_processing.hpp"

// All non-reversible algorithms return pointer to generated image or nullptr on failure. 
// Input image is never changed.
// It is user's responsibility to free memory of new image

// For list of log messages refer to "logs_image_processing.hpp"
static Logger &logs = Logger::get_instance();

enum Channels { RED, GREEN, BLUE };

// Non-reversible algorithm.
Image *extract_channel(const Image &IMAGE, const int CHANNEL) {
  if (IMAGE.has_exceptions()) {
    logs.add_log(FUNCTIONS[F_EXTRACT_CHANNEL] + ERRORS[E_INVALID_IMAGE]);
    return nullptr;
  }
  if (!IMAGE.is_tricolor()) {
    logs.add_log(FUNCTIONS[F_EXTRACT_CHANNEL] + ERRORS[E_IMAGE_NOT_RGB]);
    return nullptr;
  }
  if (CHANNEL != RED && CHANNEL != GREEN && CHANNEL != BLUE) {
    logs.add_log(FUNCTIONS[F_EXTRACT_CHANNEL] + ERRORS[E_INVALID_CHANNEL]);
    return nullptr;
  }
  // Pixel count of new image will be 3 times less than of input image's
  const int NEW_SIZE{IMAGE.get_size() / 3};
  unsigned char *new_data = new unsigned char[NEW_SIZE];
  const unsigned char *OLD_DATA = IMAGE.get_data();
  // Algorithm
  for (int i{0}; i < NEW_SIZE; ++i) {
    new_data[i] = OLD_DATA[i * 3 + CHANNEL];
  }
  logs.add_log(FUNCTIONS[F_EXTRACT_CHANNEL] + ACTIONS[A_EXTRACT_CHANNEL]);
  return new Image{IMAGE.get_width(), IMAGE.get_height(), 1, new_data};
}

// Extracts RED channel from RGB image
Image *extract_RED(const Image &IMAGE) { return extract_channel(IMAGE, RED); }

// Extracts GREEN channel from RGB image
Image *extract_GREEN(const Image &IMAGE) { return extract_channel(IMAGE, GREEN); }

// Extracts BLUE channel from RGB image
Image *extract_BLUE(const Image &IMAGE) { return extract_channel(IMAGE, BLUE); }
