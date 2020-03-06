/***************************************** User Interface Handling *****************************************/

#include "buffer.hpp"
#include "image.hpp"
#include "image_processing.hpp"
#include "logger.hpp"
#include "process_user_commands.hpp"
#include <iostream>
#include <string>

static Logger &logs = Logger::get_instance();

// UI menu options
enum Options {
  O_QUIT,
  O_LOAD,
  O_SAVE,
  O_ROTATE_CLOCKWISE,
  O_ROTATE_COUNTER_CLOCKWISE,
  O_MONOCHROME,
  O_EXTRACT_RED,
  O_EXTRACT_GREEN,
  O_EXTRACT_BLUE,
  O_QUANTIZE,
  O_CHANGE_BRIGHTNESS,
  O_HISTOGRAM,
  O_UNDO,
  O_BUFFER_INFO,
  O_IMAGE_INFO,
  O_READ_LOGS
};

// Console User Interface - returns user's command
int get_user_command() {
  std::cout << "---------------------------------------\n";
  std::cout << "\t\tMENU\n";
  std::cout << O_LOAD << " - Load Image\n";
  std::cout << O_SAVE << " - Save Image\n";
  std::cout << O_ROTATE_CLOCKWISE << " - Rotate Clockwise\n";
  std::cout << O_ROTATE_COUNTER_CLOCKWISE << " - Rotate Counter Clockwise\n";
  std::cout << O_MONOCHROME << " - RGB to Monochrome\n";
  std::cout << O_EXTRACT_RED << " - Extract Red Channel\n";
  std::cout << O_EXTRACT_GREEN << " - Extract Green Channel\n";
  std::cout << O_EXTRACT_BLUE << " - Extract Blue Channel\n";
  std::cout << O_QUANTIZE << " - Quantize\n";
  std::cout << O_CHANGE_BRIGHTNESS << " - Change Brightness\n";
  std::cout << O_HISTOGRAM << " - Calculate Histogram\n";
  std::cout << O_UNDO << " - Undo\n";
  std::cout << O_BUFFER_INFO << " - Show Buffer Information\n";
  std::cout << O_IMAGE_INFO << " - Show Image Information\n";
  std::cout << O_READ_LOGS << " - Read Logs\n";
  std::cout << O_QUIT << " - Quit\n";
  std::cout << "Enter your selection: ";
  int selection{};
  std::cin >> selection;
  return selection;
}

// Performs user selected operations, returns false if user decides to quit
bool process_user_commands(Buffer &buf) {
  bool PROCESS_COMMANDS{true};
  int user_selection = get_user_command();
  switch (user_selection) {
  case O_LOAD: {
    std::string path;
    std::cout << "Enter JPEG path: ";
    std::cin >> path;
    buf.push(Image{path});
    break;
  }
  case O_SAVE: {
    buf.top().save();
    break;
  }
  case O_ROTATE_CLOCKWISE: {
    rotate_clockwise(buf.top());
    break;
  }
  case O_ROTATE_COUNTER_CLOCKWISE: {
    rotate_counter_clockwise(buf.top());
    break;
  }
  case O_MONOCHROME: {
    Image *im = monochrome(buf.top());
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_EXTRACT_RED: {
    Image *im = extract_RED(buf.top());
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_EXTRACT_GREEN: {
    Image *im = extract_GREEN(buf.top());
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_EXTRACT_BLUE: {
    Image *im = extract_BLUE(buf.top());
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_QUANTIZE: {
    int levels{};
    std::cout << "Enter quantiation levels: ";
    std::cin >> levels;
    Image *im = quantize(buf.top(), levels);
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_CHANGE_BRIGHTNESS: {
    int change_val{};
    std::cout << "Enter change value: ";
    std::cin >> change_val;
    Image *im = change_brightness(buf.top(), change_val);
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_HISTOGRAM: {
    Image *im = histogram(buf.top());
    if (im != nullptr) {
      buf.push(*im);
    }
    break;
  }
  case O_UNDO: {
    buf.pop();
    break;
  }
  case O_BUFFER_INFO: {
    buf.info();
    break;
  }
  case O_IMAGE_INFO: {
    buf.top().info();
    break;
  }
  case O_READ_LOGS: {
    logs.read_logs();
    break;
  }
  case O_QUIT: {
    PROCESS_COMMANDS = false;
    break;
  }
  default:
    std::cout << "Unknow command\n";
    break;
  }
  return PROCESS_COMMANDS;
}