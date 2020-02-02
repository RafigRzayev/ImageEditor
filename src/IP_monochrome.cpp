#include "../include/image_processing.hpp"
#include "../include/logger.hpp"
#include "../include/logs_image_processing.hpp"

// All non-reversible algorithms return pointer to generated image or nullptr on failure.
// Input image is never changed.
// It is user's responsibility to free memory of new image

// For list of log messages refer to "logs_image_processing.hpp"
static Logger &logs = Logger::get_instance();

// Non-reversible algorithm
// Converts RGB image to monochrome. 
Image *monochrome(const Image &IMAGE) {
  if (IMAGE.has_exceptions()) {
    logs.add_log(FUNCTIONS[F_MONOCHROME] + ERRORS[E_INVALID_IMAGE]);
    return nullptr;
  }
  if (!IMAGE.is_tricolor()) {
    logs.add_log(FUNCTIONS[F_MONOCHROME] + ERRORS[E_IMAGE_NOT_RGB]);
    return nullptr;
  }
  // Pixel count of new image will be 3 times less than of input image's
  const int NEW_SIZE{IMAGE.get_size() / 3};
  unsigned char *new_data = new unsigned char[NEW_SIZE];
  const unsigned char *OLD_DATA = IMAGE.get_data();
  const float R_COEF{0.2990}, G_COEF{0.5870}, B_COEF{0.1140};
  // Algorithm
  for (int i{0}; i < NEW_SIZE; ++i) {
    new_data[i] = static_cast<unsigned char>(R_COEF * OLD_DATA[3 * i] +
                                             G_COEF * OLD_DATA[3 * i + 1] +
                                             B_COEF * OLD_DATA[3 * i + 2]);
  }
  logs.add_log(FUNCTIONS[F_MONOCHROME] + ACTIONS[A_MONOCHROME]);
  return new Image{IMAGE.get_width(), IMAGE.get_height(), 1, new_data};
}