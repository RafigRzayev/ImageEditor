/******************************************** CLASS ORGANIZATION ********************************************

display.hpp - info about the class
display.cpp - implementation of class methods
image.hpp - objects to be rendered by Display
logger.hpp - singleton logger to track the class behaviour
logs_display.hpp - collection of messages to be used for logging the Display class
<SDL2/SDL.h> - SDL2 Simple DirectMedia Layer library used to display images https://www.libsdl.org/*/

/*********************************************** GENERAL INFO ***********************************************

Aim of Display class is to render objects of Image class onto screen and provide users with GUI(ongoing) to
choose operations on the image

SDL2 library provides functionality for window creation, hardware-accelerated rendering and user interaction.
 
Thus the Display class is a wrapper of SDL2 interface:
 - Constructor abstracts SDL initialization, creation of window and hardware-accelerated renderer.
 - Destructor abstracts Deallocating memory and quitting SDL2
But since the class has singleton design, ctor and dtor are called just once during the program lifetime.

The main public interface of Display class is draw() method:
SDL2 can render only two internal types: SDL_SURFACE (for CPU rendering) and SDL_TEXTURE (for GPU rendering).
Hence Image must be converted into SDL_TEXTURE format through following chain:
  Image -> SDL_Surface -> SDL_Texture
  NOTE: Copying of pixel values occur only during texture creation, surface generation doesn't copy values.
  
Whenever draw() method is called by the user, image_to_texture() private function generates temporary 
SDL_SURFACE based on the Image. Then, it deallocates old data from TEXTURE_ member variable to prevent memory leak.
Afterwards, new SDL_TEXTURE is generated based on the Surface, and assigned to TEXTURE_. New texture is fed to 
renderer in draw() and thus image gets displayed.

Important point is that draw() method doesn't disrupt user experience when invalid image has been passed or 
when there was an exception. It is useful since user will try to render results of image processing operations.
If external failure happenns, instead of getting blank/garbage screen, previous image will be kept on it.

Only problem may occur when user undo's operations. E.g. let's say we load an image. Then we undo the loading. 
Since input to draw() is empty/garbage, last loaded image would be shown on the screen. However screen should 
be blank in this scenario. Use clear_screen() function for this purpose. */

/******************************************* DISPLAY CLASS HEADER ******************************************/

#pragma once

#include <SDL2/SDL.h>
#include "image.hpp"

class Display {
public:
  // Call for singleton
  static Display &get_instance() {
    static Display DISPLAY_;
    return DISPLAY_;
  }
  // Render an image object
  void draw(const Image& IMAGE);
  // Clear the screen
  void clear_screen();
  // Destructor
  ~Display();

private:
  // Constructor
  Display();
  // Convert Image to Texture
  bool image_to_texture(const Image& IMAGE);
  // Maximum image width supported by renderer
  int max_width() const;
  // Maximum image height supported by renderer
  int max_height() const;

  // Member variables
  const char *WINDOW_NAME_ = "Image Editor";
  const int WINDOW_WIDTH_{640};
  const int WINDOW_HEIGHT_{480};
  SDL_Window *WINDOW_{nullptr};
  SDL_Renderer *RENDERER_{nullptr};
  SDL_Texture *TEXTURE_{nullptr};
  bool initialized_{false}; 
  SDL_Color colors_[256];

  // Disables for Singleton Pattern
  Display(const Display &) = delete;
  Display(Display &&) = delete;
  Display &operator=(const Display &) = delete;
  Display &operator=(Display &&) = delete;
};
