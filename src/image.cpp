/*************************************** IMAGE CLASS IMPLEMENTATION ****************************************/

#include <iostream>
#include <string>
#include "../include/image.hpp"
#include "../include/logger.hpp"
#include "../include/logs_image.hpp"
#include "../include/helper_functions.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

// Refer to logs_image.hpp for logging info
static Logger &logs = Logger::get_instance();
size_t Image::compression_rate_{85};

/******************************************** PUBLIC FUNCTIONS *********************************************/

// DEFAULT CONSTRUCTOR - empty image
Image::Image() {
  logs.add_log(METHODS[M_DEFAULT_CTOR] + ACTIONS[A_CREATE_EMPTY_IMAGE]);
}

// USER-DEFINED CONSTRUCTOR - creat image from data (doesn't copy)
Image::Image(int WIDTH, int HEIGHT, int CHANNELS, unsigned char *DATA) {
  logs.add_log(METHODS[M_DATA_CTOR]);
  if (has_exceptions(WIDTH, HEIGHT, CHANNELS, DATA)) {
    return;
  }
  data_ = DATA;
  update_params(WIDTH, HEIGHT, CHANNELS);
  logs.add_log(ACTIONS[A_CREATE_IMAGE]);
}

// USER-DEFINED CONSTRUCTOR - create image from JPEG
Image::Image(const std::string &JPEG_PATH) {
  logs.add_log(METHODS[M_JPEG_CTOR]);
  data_ = stbi_load(JPEG_PATH.c_str(), &width_, &height_, &channels_, 0);
  if (is_empty()) {
    logs.add_log(ERRORS[E_UNABLE_TO_LOAD]);
    return;
  }
  logs.add_log(ACTIONS[A_CREATE_IMAGE]);
}

// COPY CONSTRUCTOR
Image::Image(const Image &RHS) {
  logs.add_log(METHODS[M_COPY_CTOR]);
  if (has_exceptions(RHS.width_, RHS.height_, RHS.channels_, RHS.data_)) {
    return;
  }
  init(RHS.width_, RHS.height_, RHS.channels_, RHS.data_);
  logs.add_log(ACTIONS[A_CREATE_IMAGE]);
}

// MOVE CONSTRUCTOR
Image::Image(Image &&rhs) noexcept {
  logs.add_log(METHODS[M_MOVE_CTOR]);
  if (has_exceptions(rhs.width_, rhs.height_, rhs.channels_, rhs.data_)) {
    return;
  }
  data_ = rhs.data_;
  rhs.data_ = nullptr;
  update_params(rhs.width_, rhs.height_, rhs.channels_);
  logs.add_log(ACTIONS[A_CREATE_IMAGE]);
}

// COPY ASSIGNMENT
Image &Image::operator=(const Image &RHS) {
  logs.add_log(METHODS[M_COPY_ASSIGNMENT]);
  if (this == &RHS) {
    logs.add_log(ACTIONS[A_COPY_IMAGE]);
    return *this;
  }
  if (has_exceptions(RHS.width_, RHS.height_, RHS.channels_, RHS.data_)) {
    return *this;
  }
  delete[] data_;
  data_ = nullptr;
  init(RHS.width_, RHS.height_, RHS.channels_, RHS.data_);
  logs.add_log(ACTIONS[A_COPY_IMAGE]);
  return *this;
}

// MOVE ASSIGNMENT
Image &Image::operator=(Image &&rhs) {
  logs.add_log(METHODS[M_MOVE_ASSIGNMENT]);
  if (has_exceptions(rhs.width_, rhs.height_, rhs.channels_, rhs.data_)) {
    return *this;
  }
  delete[] data_;
  data_ = rhs.data_;
  rhs.data_ = nullptr;
  update_params(rhs.width_, rhs.height_, rhs.channels_);
  logs.add_log(ACTIONS[A_COPY_IMAGE]);
  return *this;
}

// DESTRUCTOR
Image::~Image() {
  logs.add_log(METHODS[M_DTOR]);
  if (is_empty()) {
    logs.add_log(ACTIONS[A_DESTROY_EMPTY_IMAGE]);
    return;
  }
  logs.add_log(ACTIONS[A_DESTROY_IMAGE]);
  delete[] data_;
}

// LOAD IMAGE
bool Image::load(const std::string &JPEG_PATH) {
  logs.add_log(METHODS[M_LOAD]);
  unsigned char *temp_data = stbi_load(JPEG_PATH.c_str(), &width_, &height_, &channels_, 0);
  if (is_empty(temp_data)) {
    logs.add_log(ERRORS[E_UNABLE_TO_LOAD]);
    return false;
  }
  delete [] data_;
  data_ = temp_data;
  logs.add_log(ACTIONS[A_LOAD_IMAGE]);
  return true;  
}

// SAVE IMAGE
bool Image::save(const std::string &JPEG_PATH) const {
  logs.add_log(METHODS[M_SAVE]);
  if(has_exceptions(width_, height_, channels_, data_)) {
    return false;
  }
  stbi_write_jpg(JPEG_PATH.c_str(), width_, height_, channels_, data_, compression_rate_);
  logs.add_log(ACTIONS[A_SAVE_IMAGE]);
  return true;
}

// IMAGE INFORMATION
void Image::info() const {
  std::cout << "---------------------------------------\n";
  std::cout << "\tIMAGE INFORMATION\n";
  std::cout << " - Width: " << width_ << std::endl;
  std::cout << " - Height: " << height_ << std::endl;
  std::cout << " - Channels: " << channels_ << std::endl;
  std::cout << " - Size: ";
  print_memory(get_size());
  std::cout << " - Address of data: ";
  if (is_empty()) {
    std::cout << "nullptr" << std::endl;
  } else {
    std::cout << static_cast<void *>(data_) << std::endl;
  }
}

// CHECK IF THE IMAGE IS EMPTY
bool Image::is_empty() const { return is_empty(data_); }

// CHECK IF IMAGE HAS EXCEPTION
bool Image::has_exceptions() const {   
  if (is_empty(data_)) {
    return true;
  }
  if (invalid_channels(channels_)) {
    return true;
  }
  if (non_positive_dimensions(width_, height_)) {
    return true;
  }
  if (size_overflow(width_, height_, channels_)) {
    return true;
  }
  return false;
}

// CHECK IF IMAGE IS MONOCOLOR
bool Image::is_monocolor() const { return channels_ == 1; }

// CHECK IF IMAGE IS TRICOLOR
bool Image::is_tricolor() const { return channels_ == 3; }

// GET IMAGE WIDTH
int Image::get_width() const { return width_; }

// GET IMAGE HEIGHT
int Image::get_height() const { return height_; }

// GET NUMBER OF CHANNELS
int Image::get_channels() const { return channels_; }

// GET IMAGE DATA
const unsigned char *Image::get_data() const { return data_; }

// GET IMAGE SIZE (PIXEL COUNT)
int Image::get_size() const {
  return width_ * height_ * channels_;
} 

/******************************************** PRIVATE FUNCTIONS ********************************************/

// CHECK IF A DATA SEQUENCE IS EMPTY
bool Image::is_empty(const unsigned char *DATA) const {
  return DATA == nullptr;
}

// CHECK IF A CHANNEL VALUE IS INVALID
bool Image::invalid_channels(int CHANNELS) const {
  return CHANNELS != 1 && CHANNELS != 3;
}

// CHECK IF IMAGE DIMENSIONS ARE NOT POSITIVE
bool Image::non_positive_dimensions(int WIDTH, int HEIGHT) const {
  return WIDTH <= 0 || HEIGHT <= 0;
}

// CHECK IF MULTIPLICATION CAUSES INT OVERFLOW
bool Image::multiplication_overflow(const int A, const int B) const {
  if(A == 0 || B == 0) {
    return false;
  }
  return (A * B) / A != B;
}

// CHECK IF IMAGE SIZE IS MORE THAN INT::MAX
bool Image::size_overflow(int WIDTH, int HEIGHT, int CHANNELS) const {
  return multiplication_overflow(WIDTH, HEIGHT) || multiplication_overflow(WIDTH * HEIGHT, CHANNELS);
}
// CHECK EXCEPTIONS, UPDATE LOGS
bool Image::has_exceptions(int WIDTH, int HEIGHT, int CHANNELS,
                            const unsigned char *DATA) const {
  if (is_empty(DATA)) {
    logs.add_log(ERRORS[E_EMPTY_DATA]);
    return true;
  }
  if (invalid_channels(CHANNELS)) {
    logs.add_log(ERRORS[E_INVALID_CHANNELS]);
    return true;
  }
  if (non_positive_dimensions(WIDTH, HEIGHT)) {
    logs.add_log(ERRORS[E_NON_POSITIVE_DIMENSIONS]);
    return true;
  }
  if (size_overflow(WIDTH, HEIGHT, CHANNELS)) {
    logs.add_log(ERRORS[E_IMAGE_SIZE_OVERFLOW]);
    return true;
  }
  return false;
}

// UPDADE THE IMAGE PARAMETERS TO NEW VALUES - NO EXCEPTION HANDLING TO AVOID DUPLICATE CHECKS
void Image::update_params(int WIDTH, int HEIGHT, int CHANNELS) {
  width_ = WIDTH;
  height_ = HEIGHT;
  channels_ = CHANNELS;
}

// INITIALIZE THE IMAGE - NO EXCEPTION HANDLING TO AVOID DUPLICATE CHECKS
void Image::init(int WIDTH, int HEIGHT, int CHANNELS,
                 const unsigned char *DATA) {
  const int DATA_COUNT{WIDTH * HEIGHT * CHANNELS};
  data_ = new unsigned char[DATA_COUNT];
  for (int i{0}; i < DATA_COUNT; ++i) {
    data_[i] = DATA[i];
  }
  update_params(WIDTH, HEIGHT, CHANNELS);
}
