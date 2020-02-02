/*************************************** BUFFER CLASS IMPLEMENTATION ***************************************/

#include "../include/buffer.hpp"
#include "../include/logs_buffer.hpp"
#include "../include/image.hpp"
#include "../include/logger.hpp"
#include "../include/print_memory.hpp"
#include <iostream>
#include <list>

// refer to logs_buffer.hpp for logging info
static Logger &logs = Logger::get_instance();

// CONSTRUCTOR
Buffer::Buffer() { logs.add_log(METHODS[M_CTOR] + ACTIONS[A_CREATE_BUFFER]); }

// DESTRUCTOR
Buffer::~Buffer() {
  flush_buffer();
  logs.add_log(METHODS[M_DTOR] + ACTIONS[A_DESTROY_BUFFER]);
}

// ADD IMAGE TO THE BUFFER - for lvalue images (same code for rvalues)
void Buffer::push(Image &IMAGE) {
  // Exceptions
  if (IMAGE.has_exceptions()) {
    logs.add_log(METHODS[M_PUSH] + ERRORS[E_INVALID_IMAGE]);
    return;
  }
  const size_t NEW_IMAGE_SIZE = IMAGE.get_size();
  if (NEW_IMAGE_SIZE > MAX_MEMORY_) {
    logs.add_log(METHODS[M_PUSH] + ERRORS[E_GIANT_IMAGE]);
    return;
  }
  // Release front elements from buffer until image can be pushed
  while (CURRENT_MEMORY_ + NEW_IMAGE_SIZE > MAX_MEMORY_) {
    std::cout << "BEEN HERE";
    logs.add_log(METHODS[M_PUSH] + ACTIONS[A_FREE_MEMORY]);
    const size_t FIRST_IMAGE_SIZE = Buffer_.front().get_size();
    if (FIRST_IMAGE_SIZE > CURRENT_MEMORY_ || Buffer_.empty()) {
      logs.add_log(METHODS[M_PUSH] + ERRORS[E_CORRUPTED_BUFFER]);
      flush_buffer();
      break;
    }
    CURRENT_MEMORY_ -= FIRST_IMAGE_SIZE;
    Buffer_.pop_front();
  }
  // Push
  CURRENT_MEMORY_ += NEW_IMAGE_SIZE;
  Buffer_.push_back(std::move(IMAGE));
  logs.add_log(METHODS[M_PUSH] + ACTIONS[A_PUSH_IMAGE]);
}

// ADD IMAGE TO THE BUFFER - for rvalue images(same code for lvalues)
void Buffer::push(Image &&IMAGE) {
  // Exceptions
  if (IMAGE.has_exceptions()) {
    logs.add_log(METHODS[M_PUSH] + ERRORS[E_INVALID_IMAGE]);
    return;
  }
  const size_t NEW_IMAGE_SIZE = IMAGE.get_size();
  if (NEW_IMAGE_SIZE > MAX_MEMORY_) {
    logs.add_log(METHODS[M_PUSH] + ERRORS[E_GIANT_IMAGE]);
    return;
  }
  // Release front elements from buffer until image can be pushed
  while (CURRENT_MEMORY_ + NEW_IMAGE_SIZE > MAX_MEMORY_) {
    std::cout << "BEEN HERE";
    logs.add_log(METHODS[M_PUSH] + ACTIONS[A_FREE_MEMORY]);
    const size_t FIRST_IMAGE_SIZE = Buffer_.front().get_size();
    if (FIRST_IMAGE_SIZE > CURRENT_MEMORY_ || Buffer_.empty()) {
      logs.add_log(METHODS[M_PUSH] + ERRORS[E_CORRUPTED_BUFFER]);
      flush_buffer();
      break;
    }
    CURRENT_MEMORY_ -= FIRST_IMAGE_SIZE;
    Buffer_.pop_front();
  }
  // Push
  CURRENT_MEMORY_ += NEW_IMAGE_SIZE;
  Buffer_.push_back(std::move(IMAGE));
  logs.add_log(METHODS[M_PUSH] + ACTIONS[A_PUSH_IMAGE]);
}

// REMOVE IMAGE FROM THE BUFFER
void Buffer::pop() {
  // Exceptions
  if (Buffer_.empty()) {
    logs.add_log(METHODS[M_POP] + ERRORS[E_POP_EMPTY]);
    return;
  }
  const size_t LAST_IMAGE_SIZE = Buffer_.back().get_size();
  if (LAST_IMAGE_SIZE > CURRENT_MEMORY_) {
    logs.add_log(METHODS[M_POP] + ERRORS[E_CORRUPTED_BUFFER]);
    flush_buffer();
    return;
  }
  // Pop
  CURRENT_MEMORY_ -= LAST_IMAGE_SIZE;
  Buffer_.pop_back();
  logs.add_log(METHODS[M_POP] + ACTIONS[A_POP_IMAGE]);
}

// RETURN LAST IMAGE IN THE BUFFER
Image &Buffer::top() {
  if (Buffer_.empty()) {
    logs.add_log(METHODS[M_TOP] + ERRORS[E_TOP_EMPTY]);
  }
  return Buffer_.back();
}

// CLEAR CONTENTS OF THE BUFFER
void Buffer::flush_buffer() {
  Buffer_.clear();
  CURRENT_MEMORY_ = 0;
  logs.add_log(METHODS[M_FLUSH_BUFFER] + ACTIONS[A_FLUSH_BUFFER]);
}

// BUFFER INFORMATION
void Buffer::info() {
  std::cout << "---------------------------------------\n";
  std::cout << "\tBUFFER INFORMATION\n";
  std::cout << "Number of images: " << Buffer_.size() << std::endl;
  std::cout << "Current memory: ";
  print_memory(CURRENT_MEMORY_); // prints in kB, MB, GB format
  std::cout << "Max memory limit: ";
  print_memory(MAX_MEMORY_);
}

// CHECK IF BUFFER IS EMPTY
bool Buffer::is_empty() {
  return Buffer_.empty();
}