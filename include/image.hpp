/******************************************** CLASS ORGANIZATION ********************************************

image.hpp - info about the class
image.cpp - implementation of class methods
logger.hpp - singleton logger to track the class behaviour
image_logs.hpp - collection of messages to be used for logging the image class
<iostream> - to print image information to console
stb_image.h - image loading -> https://github.com/nothings/stb/blob/master/stb_image.h
stb_image_write.h - image writing -> https://github.com/nothings/stb/blob/master/stb_image_write.h*/

/*********************************************** GENERAL INFO ***********************************************

The Image class supports 1 or 3 channel 8-bit JPEG format.

It uses stb_image.h and stb_image_write.h for decoding(loading) and encoding(saving) JPEG files.
Max image size (i.e. WIDTH x HEIGTH x CHANNELS x BIT_DEPTH) is INT::MAX bytes. 

The limit is according to the stb_image.h -> https://github.com/nothings/stb/blob/master/stb_image.h: 

  "// stb_image uses ints pervasively, including for offset calculations.
  // therefore the largest decoded image size we can support with the
  // current code, even on 64-bit targets, is INT_MAX. this is not a
  // significant limitation for the intended use case.
  //
  // we do, however, need to make sure our size calculations don't
  // overflow. hence a few helper functions for size calculations that
  // multiply integers together, making sure that they're non-negative
  // and no overflow occurs."

On most systems INT is 4 bytes (32 bits), so: INT::MAX =  (2^32)/2 - 1 = 2147483647 bytes ≈ 2GB.

  Example for size determination: 
    W = 1000 pixels, H = 2000 pixels, C = 3 (RGB). BIT_DEPTH = 8 bits (1 byte). 
    Size = W*H*C*Byte = 6000000 Bytes = 6000000 / (1024*1024) MB = 5.72 MB. */

/******************************************* IMAGE CLASS HEADER ********************************************/

#pragma once

#include <string>

class Image {
public:
  // Default Constructor - Empty image
  Image();
  // User-defined Constructor - Create image from data (doesn't copy)
  Image(int WIDTH, int HEIGHT, int CHANNELS, unsigned char *DATA);
  // User-defined Constructor - Create image from JPG file
  Image(const std::string &JPEG_PATH);
  // Copy Constructor
  Image(const Image &RHS);
  // Move Constructor
  Image(Image &&rhs) noexcept;
  // Copy assignment
  Image &operator=(const Image &RHS);
  // Move assignment
  Image &operator=(Image &&rhs);
  // Destructor
  ~Image();
  // Load Image
  bool load(const std::string &JPEG_PATH = "../gallery/default.jpg");
  // Save Image
  bool save(const std::string &JPEG_PATH = "../gallery/NEW_SAVE.jpg") const;
  // Image information
  void info() const;
  // Check if the image is empty
  bool is_empty() const;
  // Check if image is valid
  bool has_exceptions() const;
  // Check if image is monocolor
  bool is_monocolor() const;
  // Check if image is tricolor
  bool is_tricolor() const;
  // Get image width
  int get_width() const;
  // Get image height
  int get_height() const;
  // Get number of channels
  int get_channels() const;
  // Get image data
  const unsigned char *get_data() const;
  // Get image size (pixel count)
  int get_size() const;

private:
  bool is_empty(const unsigned char *DATA) const;
  bool invalid_channels(int CHANNELS) const;
  bool non_positive_dimensions(int WIDTH, int HEIGHT) const;
  bool multiplication_overflow(const int A, const int B) const;
  bool size_overflow(int WIDTH, int HEIGHT, int CHANNELS) const;
  bool has_exceptions(int WIDTH, int HEIGHT, int CHANNELS, const unsigned char *DATA) const;
  void update_params(int WIDTH, int HEIGHT, int CHANNELS);
  void init(int WIDTH, int HEIGHT, int CHANNELS, const unsigned char *DATA);

  // Member variables
  int width_{0};
  int height_{0};
  int channels_{0};
  unsigned char *data_{nullptr};
  static size_t compression_rate_;
};
