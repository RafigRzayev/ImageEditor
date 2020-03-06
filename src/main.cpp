#include "buffer.hpp"
#include "display.hpp"
#include "process_user_commands.hpp"

Display &Display = Display::get_instance();

int main() {
  Buffer ImageBuffer{};
  while (process_user_commands(ImageBuffer)) {
    if (ImageBuffer.is_empty()) {
      Display.clear_screen();
    } else {
      Display.draw(ImageBuffer.top());
    }
  }
  return 0;
}
