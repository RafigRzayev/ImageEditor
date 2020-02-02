/**************************************** BUFFER CLASS ORGANIZATION *****************************************

buffer.hpp - info about the class
buffer.cpp - implementation of class methods
logger.hpp - singleton logger to track the class behaviour
logs_buffer.hpp - collection of messages to be used for logging the buffer
image.hpp - Buffer objects
print_memory.hpp - prints memory indicator based on its value - in Bytes, kB, MB, GB etc.
<iostream> - to print buffer information to console
<list> - std::list is used for modelling the Image Buffer*/

/*********************************************** GENERAL INFO ***********************************************

Aim of buffer class is to provide user the ability to undo image processing operations (i.e. CTRL + Z). Once
user loads an image, it will be the first element of the buffer. With each operation, updated image will
be pushed onto buffer and next image processing operation will be done with the last pushed image.

Buffer has a memory limit which is 1 GB and could be updated in the code(MAX_MEMORY_). This eliminates PC 
slowdown and possible crash due to attempting to use more RAM than OS has allocated for programs. We cannot
push any image with size more than MAX_MEMORY_, and sum of image sizes in the buffer cannot exceed MAX_MEMORY_.

To track it, CURRENT_MEMORY_ variable is used. It is updated on each image insertion and deletion. If pushing 
an image will cause buffer overflow(i.e. CURRENT_MEMORY_ > MAX_MEMORY_), then old elements of the buffer 
are deleted to free space for the new image. Once no overflow condition is met, image will be pushed.

Insertion and deletion are abstracted with push() and pop() methods. User should interface just with the last
image in the buffer, thus top() method is provided with analogy to the stack data structure. 

Since deletions are happening just in the end or start of the buffer(in pop and in memory release during push),
and new images are always appended to the end of the buffer, list data structure have been selected. Also,
because buffer size is not known(in terms of number of elements), and due to frequent size changes (with each 
push and pop), list data structure seems as better choice compared to an array. List is implemented via std::list

When user activates image processing function, generated image will be pushed into buffer. When user decides to
undo, last image will be popped and user will get original image. Only exception is when image processing algorithms
are reversible (e.g. rotation). In that case, there is no need to store additional memory, image should be updated 
instead of being pushed.*/

/******************************************* BUFFER CLASS HEADER *******************************************/

#pragma once

#include "image.hpp"
#include <list>

class Buffer {
public:
  // Constructor
  Buffer();
  // Destructor
  ~Buffer();
  // Add image to the buffer (lvalue)
  void push(Image &IMAGE);
  // Add image to the buffer (rvalue)
  void push(Image &&IMAGE);
  // Remove image from the buffer
  void pop();
  // Return last image in the buffer
  Image &top();
  // Clear contents of the buffer
  void flush_buffer();
  // Buffer information
  void info();
  // Check if buffer is empty
  bool is_empty();

private:
  // Member variables
  std::list<Image> Buffer_{};
  size_t CURRENT_MEMORY_{0};
  static const size_t MAX_MEMORY_{1000000000}; // 1 GB

  // Not required at the moment:
  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&r) = delete;
  Buffer &operator=(const Buffer &) = delete;
  Buffer &operator=(Buffer &&) = delete;
};