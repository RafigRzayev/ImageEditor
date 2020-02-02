/************************************ DATA FOR LOGGING THE BUFFER CLASS ************************************/

// Use ARRAY_NAME[KEYWORD] to access desired log message string. 

#pragma once

#include <string>

// Keywords for class methods. Naming format: M_METHOD_NAME
enum Methods {
  M_CTOR,
  M_DTOR,
  M_PUSH,
  M_POP,
  M_TOP,
  M_FLUSH_BUFFER,
  M_COUNT
};

// Array of method names 
const std::string METHODS[M_COUNT] {
  "BUFFER - Constructor -> ",
  "BUFFER - Destructor -> ",
  "BUFFER - push() -> ",
  "BUFFER - pop() -> ",
  "BUFFER - top() -> ",
  "BUFFER - flush_buffer() -> "
};

// Keywords for errors. Naming format: E_ERROR_NAME
enum Errors {
  E_INVALID_IMAGE,
  E_GIANT_IMAGE,
  E_CORRUPTED_BUFFER,
  E_POP_EMPTY,
  E_TOP_EMPTY,
  E_COUNT
};

// Array of error messages
const std::string ERRORS[E_COUNT] {
  "ERROR: Can't push invalid image\n", 
  "ERROR: Image size exceeds maximum memory limit\n",
  "ERROR: Corrupted Buffer\n",
  "ERROR: Buffer is already empty\n",
  "ERROR: Returning garbage value from an empty buffer\n"
};

// Keywords for actions. Naming format: A_ACTION_NAME
enum Actions {
  A_CREATE_BUFFER,
  A_DESTROY_BUFFER,
  A_FLUSH_BUFFER,
  A_FREE_MEMORY,
  A_PUSH_IMAGE,
  A_POP_IMAGE,
  A_COUNT
};

// Array of action messages
const std::string ACTIONS[A_COUNT] {
  "Buffer has been created\n",
  "Buffer has been destroyed\n",
  "Clearing the buffer...\n",
  "Creating space for push...\n",
  "Image has been pushed\n",
  "Image has been popped\n",
};