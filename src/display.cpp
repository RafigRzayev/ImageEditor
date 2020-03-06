/*************************************** DISPLAY CLASS IMPLEMENTATION **************************************/

#include "display.hpp"
#include "image.hpp"
#include "logger.hpp"
#include "logs_display.hpp"
#include <SDL2/SDL.h>

// Refer to logs_display.hpp for logging info
Logger &logs = Logger::get_instance();

// Functions with names SDL_FUNC_NAME are part of SDL library

// CONSTRUCTOR - PREPARES RENDERING ENVIRONMENT
Display::Display() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    logs.add_log(METHODS[M_CTOR] + ERRORS[E_SDL_INIT]);
    return;
  }
  // Create SDL Window
  WINDOW_ = SDL_CreateWindow(WINDOW_NAME_, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH_,
                             WINDOW_HEIGHT_, SDL_WINDOW_SHOWN);
  if (WINDOW_ == nullptr) {
    logs.add_log(METHODS[M_CTOR] + ERRORS[E_SDL_CREATE_WINDOW]);
    return;
  }
  // Create SDL Renderer
  RENDERER_ = SDL_CreateRenderer(WINDOW_, -1, SDL_RENDERER_ACCELERATED);
  if (RENDERER_ == nullptr) {
    logs.add_log(METHODS[M_CTOR] + ERRORS[E_SDL_CREATE_RENDERER]);
    return;
  }
  // Set background color for empty screen
  if (SDL_SetRenderDrawColor(RENDERER_, 0xFF, 0xFF, 0xFF, 0xFF) != 0) {
    logs.add_log(METHODS[M_CTOR] + ERRORS[E_SDL_SET_RENDER_DRAW_COLOR]);
    return;
  }
  // Show empty screen
  if (SDL_RenderClear(RENDERER_) != 0) {
    logs.add_log(METHODS[M_CTOR] + ERRORS[E_SDL_RENDER_CLEAR]);
    return;
  }
  SDL_RenderPresent(RENDERER_);
  // Required data for grayscale surface generation in image_to_texture()
  for (size_t i{0}; i < 256; i++) {
    colors_[i].r = colors_[i].g = colors_[i].b = i;
  }
  // Set flag if initialization was successfull
  initialized_ = true;
  logs.add_log(METHODS[M_CTOR] + ACTIONS[A_CREATE_DISPLAY]);
}

// DESTRUCTOR - Order is important
Display::~Display() {
  SDL_DestroyTexture(TEXTURE_);
  SDL_DestroyRenderer(RENDERER_);
  SDL_DestroyWindow(WINDOW_);
  SDL_Quit();
  logs.add_log(METHODS[M_DTOR] + ACTIONS[A_DESTROY_DISPLAY]);
}

// RENDER AN IMAGE OBJECT - in case of exception, previous image is kept on the screen
void Display::draw(const Image &IMAGE) {
  // Invalid image
  if (IMAGE.has_exceptions()) {
    logs.add_log(METHODS[M_DRAW] + ERRORS[E_INVALID_IMAGE]);
    return;
  }
  // SDL was not initialized properly
  if (!initialized_) {
    logs.add_log(METHODS[M_DRAW] + ERRORS[E_UNINITIALIZED_DISPLAY]);
    return;
  }
  // Image dimensions exceed hardware limitation for rendering
  if (IMAGE.get_width() >= max_width() || IMAGE.get_height() >= max_height()) {
    logs.add_log(METHODS[M_DRAW] + ERRORS[E_GIANT_IMAGE]);
    return;
  }
  // Convert image to texture
  if (!image_to_texture(IMAGE)) {
    logs.add_log(METHODS[M_DRAW] + ERRORS[E_IMAGE_TO_TEXTURE]);
    return;
  }
  // Update RENDERER_ with new texture
  if (SDL_RenderCopy(RENDERER_, TEXTURE_, NULL, NULL) != 0) {
    logs.add_log(METHODS[M_DRAW] + ERRORS[E_SDL_RENDER_COPY]);
    return;
  }
  // Draw image to the screen
  SDL_RenderPresent(RENDERER_);
  logs.add_log(METHODS[M_DRAW] + ACTIONS[A_DRAW_IMAGE]);
}

// CLEAR THE SCREEN
void Display::clear_screen() {
  SDL_RenderClear(RENDERER_);
  SDL_RenderPresent(RENDERER_);
}

// CONVERT IMAGE TO TEXTURE - All exceptions are checked in draw()
bool Display::image_to_texture(const Image &IMAGE) {
  // Variables to build a surface from image
  SDL_Surface *tmp_Surface{nullptr};
  void *data = const_cast<unsigned char *>(IMAGE.get_data());
  const int WIDTH{IMAGE.get_width()}, HEIGHT{IMAGE.get_height()};
  const int CHANNELS{IMAGE.get_channels()};
  const int DEPTH{CHANNELS * 8}, PITCH{WIDTH * CHANNELS};
  // RGB surface generation
  if (IMAGE.is_tricolor()) {
    tmp_Surface = SDL_CreateRGBSurfaceWithFormatFrom(
        data, WIDTH, HEIGHT, DEPTH, PITCH, SDL_PIXELFORMAT_RGB24);
  }
  // Monochrome surface generation
  else {
    tmp_Surface = SDL_CreateRGBSurfaceWithFormatFrom(
        data, WIDTH, HEIGHT, DEPTH, PITCH, SDL_PIXELFORMAT_INDEX8);
    // For 8 bit surfaces SDL generates empty palette. We need to update it
    if (SDL_SetPaletteColors(tmp_Surface->format->palette, colors_, 0, 256) != 0) {
      logs.add_log(METHODS[M_IMAGE_TO_TEXTURE] + ERRORS[E_SDL_SET_PALETTE]);
      return false;
    }
  }
  // Surface generation status
  if (tmp_Surface == nullptr) {
    logs.add_log(METHODS[M_IMAGE_TO_TEXTURE] + ERRORS[E_SDL_CREATE_SURFACE]);
    return false;
  }
  // Delete old texture -> update texture with new surface -> delete surface
  SDL_DestroyTexture(TEXTURE_);
  TEXTURE_ = SDL_CreateTextureFromSurface(RENDERER_, tmp_Surface);
  SDL_FreeSurface(tmp_Surface);
  if (TEXTURE_ == nullptr) {
    logs.add_log(METHODS[M_IMAGE_TO_TEXTURE] + ERRORS[E_SDL_CREATE_TEXTURE]);
    return false;
  }
  return true;
}

// MAXIMUM IMAGE WIDTH SUPPORTED BY RENDERER
int Display::max_width() const {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(RENDERER_, &info);
  return info.max_texture_width;
}

// MAXIMUM IMAGE HEIGHT SUPPORTED BY RENDERER
int Display::max_height() const {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(RENDERER_, &info);
  return info.max_texture_height;
}