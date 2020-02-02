/************************************* DATA FOR LOGGING THE IMAGE CLASS ************************************/

// Use ARRAY_NAME[KEYWORD] to access desired log message string. 

#pragma once

#include <string>

// Keywords for class methods. Naming format: M_METHOD_NAME
enum Methods {
  M_DEFAULT_CTOR,
  M_DATA_CTOR,
  M_JPEG_CTOR,
  M_COPY_CTOR,
  M_MOVE_CTOR,
  M_COPY_ASSIGNMENT,
  M_MOVE_ASSIGNMENT,
  M_DTOR,
  M_LOAD,
  M_SAVE,
  M_COUNT
};

// Array of method names 
const std::string METHODS[M_COUNT] {
  "IMAGE - Default Constructor -> ",
  "IMAGE - Data Constructor -> ",
  "IMAGE - JPEG Constructor -> ",
  "IMAGE - Copy Constructor -> ",
  "IMAGE - Move Constructor -> ",
  "IMAGE - Copy Assignment -> ",
  "IMAGE - Move Assignment -> ",
  "IMAGE - Destructor -> ",
  "IMAGE - load() -> ",
  "IMAGE - save() -> "
};

// Keywords for errors. Naming format: E_ERROR_NAME
enum Errors {
  E_EMPTY_DATA,
  E_INVALID_CHANNELS,
  E_NON_POSITIVE_DIMENSIONS,
  E_IMAGE_SIZE_OVERFLOW,
  E_UNABLE_TO_LOAD,
  E_COUNT
};

// Array of error messages
const std::string ERRORS[E_COUNT] {
  "ERROR: Empty data\n", 
  "ERROR: Invalid channels\n",
  "ERROR: Non-positive dimensions\n",
  "ERROR: Image size exceeds INT::MAX\n",
  "ERROR: Unable to load the JPEG\n"
};

// Keywords for actions. Naming format: A_ACTION_NAME
enum Actions {
  A_CREATE_EMPTY_IMAGE,
  A_CREATE_IMAGE,
  A_COPY_IMAGE,
  A_DESTROY_EMPTY_IMAGE,
  A_DESTROY_IMAGE,
  A_LOAD_IMAGE,
  A_SAVE_IMAGE,
  A_COUNT
};

// Array of action messages
const std::string ACTIONS[A_COUNT] {
  "Empty image has been created\n",
  "Image has been created\n",
  "Image has been copied\n",
  "Empty image has been destroyed\n",
  "Image has been destroyed\n",
  "Image has been loaded\n",
  "Image has been saved\n"
};