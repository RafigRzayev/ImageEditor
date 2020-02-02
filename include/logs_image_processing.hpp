/******************************* DATA FOR LOGGING IMAGE PROCESSING FUNCTIONS *******************************/

// Use ARRAY_NAME[KEYWORD] to access desired log message string. 

#pragma once

#include <string>

// Keywords for function names. Naming format: F_FUNCTION_NAME
enum Functions {
  F_CHANGE_BRIGHTNESS,
  F_MONOCHROME,
  F_QUANTIZE,
  F_EXTRACT_CHANNEL,
  F_HISTOGRAM,
  F_ROTATE_CLOCK,
  F_ROTATE_COUNTER_CLOCK,
  F_COUNT
};

// Array of function names
const std::string FUNCTIONS[F_COUNT] {
  "IP - change_brightness() -> ",
  "IP - monochrome() -> ",
  "IP - quantize() -> ",
  "IP - extract_channel() -> ",
  "IP - histogram() -> ",
  "IP - rotate_clockwise() -> ",
  "IP - rotate_counter_clockwise() -> "
};

// Keywords for errors. Naming format: E_ERROR_NAME
enum Errors {
  E_INVALID_IMAGE,
  E_BRIGHTNESS_CHANGE_VALUE,
  E_IMAGE_NOT_RGB,
  E_QUANTIZATION_LEVEL,
  E_INVALID_CHANNEL,
  E_IMAGE_NOT_MONOCHROME,
  E_COUNT
};

// Array of error messages
const std::string ERRORS[E_COUNT] {
  "ERROR: Invalid image\n", 
  "ERROR: Change value outside the range [-255, 255]\n",
  "ERROR: Input image should have 3 channels\n",
  "ERROR: Quantization level outside the range [2, 256]\n",
  "ERROR: Invalid channel requested\n",
  "ERROR: Input image should have 1 channel\n"
};

// Keywords for actions. Naming format: A_ACTION_NAME
enum Actions {
  A_CHANGE_BRIGHTNESS,
  A_NO_BRIGHTNESS_CHANGE,
  A_MONOCHROME,
  A_QUANTIZE,
  A_EXTRACT_CHANNEL,
  A_HISTOGRAM,
  A_ROTATE_CLOCK,
  A_ROTATE_COUNTER_CLOCK,
  A_COUNT
};

// Array of action messages
const std::string ACTIONS[A_COUNT] {
  "Brightness change successfull\n",
  "Success, but no change was made since change value is 0\n",
  "Monochrome transformation successfull\n",
  "Quantization successfull\n",
  "Channel extraction successfull\n",
  "Histogram generation successfull\n",
  "Clockwise rotation successfull\n",
  "Counter-clockwise rotation successfull\n"
};