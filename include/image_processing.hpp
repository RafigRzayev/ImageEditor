/************************************** ALL IMAGE PROCESSING FUNCTIONS *************************************/

#pragma once

#include "image.hpp"

/**************************************** Non-Reversible algorithms ****************************************/

// All non-reversible algorithms return pointer to generated image or nullptr on failure.
// Input image is never changed.
// It is user's responsibility to free memory of new image

// Converts RGB image to monochrome.
Image* monochrome(const Image &IMAGE);

// Extracts RED channel from RGB image
Image *extract_RED(const Image &IMAGE);

// Extracts GREEN channel from RGB image
Image *extract_GREEN(const Image &IMAGE);

// Extracts BLUE channel from RGB image
Image *extract_BLUE(const Image &IMAGE);

// Generates histogram of the image
Image *histogram(const Image &IMAGE);

// Changes brightness of an image. Range of change values: [-255, 255]
Image* change_brightness(const Image &IMAGE, const int CHANGE_VAL);

// Applies quantization to pixel values. Range of quantization levels: [2, 256]
Image* quantize(const Image &IMAGE, const int LEVELS);

/****************************************** Reversible algorithms ******************************************/

// All reversible algorithms change the input image.
// They return boolean representing successfull update

// Rotates the image in clockwise direction
bool rotate_clockwise(Image &IMAGE);

// Rotates the image in counter-clockwise direction
bool rotate_counter_clockwise(Image &IMAGE);