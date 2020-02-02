#include "../include/image_processing.hpp"
#include "../include/logger.hpp"
#include "../include/logs_image_processing.hpp"

// All non-reversible algorithms return pointer to generated image or nullptr on failure.
// Input image is never changed. 
// It is user's responsibility to free memory of new image

// For list of log messages refer to "logs_image_processing.hpp"
static Logger &logs = Logger::get_instance();

// Non-reversible algorithm
// Applies quantization to pixel values
// Range of quantization levels: [2, 256].
Image *quantize(const Image &IMAGE, const int LEVELS) {
  if (IMAGE.has_exceptions()) {
    logs.add_log(FUNCTIONS[F_QUANTIZE] + ERRORS[E_INVALID_IMAGE]);
    return nullptr;
  }
  if (LEVELS <= 1 || LEVELS > 256) {
    logs.add_log(FUNCTIONS[F_QUANTIZE] + ERRORS[E_QUANTIZATION_LEVEL]);
    return nullptr;
  }
  const int SIZE{IMAGE.get_size()};
  unsigned char *new_data = new unsigned char[SIZE];
  const unsigned char *OLD_DATA = IMAGE.get_data();
  const float C1{255.f / (LEVELS - 1)};
  const float C2{C1 / 2};
  // ALGORITHM
  for (int i{0}; i < SIZE; ++i) {
    new_data[i] = static_cast<int>(static_cast<int>((OLD_DATA[i] + C2) / C1) * C1);
  }
  logs.add_log(FUNCTIONS[F_QUANTIZE] + ACTIONS[A_QUANTIZE]);
  return new Image{IMAGE.get_width(), IMAGE.get_height(), IMAGE.get_channels(), new_data};
}