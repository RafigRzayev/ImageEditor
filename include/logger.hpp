/*********************************** SINGLETON LOGGER FOR WHOLE PROJECT ***********************************/

#pragma once

#include <iostream>
#include <string>

class Logger {
public:
  static Logger &get_instance() {
    static Logger LOGGER_;
    return LOGGER_;
  }
  void add_log(const std::string &LOG) { get_instance().logs_ += LOG; }
  void read_logs() const { 
    std::cout << "---------------------------------------\n";
    std::cout << get_instance().logs_; }

private:
  Logger() = default;
  Logger(const Logger &) = delete;
  Logger(Logger &&) = delete;
  Logger &operator=(const Logger &) = delete;
  Logger &operator=(Logger &&) = delete;
  std::string logs_{"\t\tLOGBOOK\n"};
};