/************************************ DATA FOR LOGGING THE DISPLAY CLASS ***********************************/

// Use ARRAY_NAME[KEYWORD] to access desired log message string. 

#pragma once

#include <string>

// Keywords for class methods. Naming format: M_METHOD_NAME
enum Methods {
  M_CTOR,
  M_DTOR,
  M_DRAW,
  M_IMAGE_TO_TEXTURE,
  M_COUNT
};

// Array of method names 
const std::string METHODS[M_COUNT] {
  "DISPLAY - Constructor -> ",
  "DISPLAY - Destructor -> ",
  "DISPLAY - draw() -> ",
  "DISPLAY - image_to_texture() -> "
};

// Keywords for errors. Naming format: E_ERROR_NAME
enum Errors {
  E_INVALID_IMAGE,
  E_UNINITIALIZED_DISPLAY,
  E_GIANT_IMAGE,
  E_IMAGE_TO_TEXTURE,
  E_SDL_RENDER_COPY,
  E_SDL_INIT,
  E_SDL_CREATE_WINDOW,
  E_SDL_CREATE_RENDERER,
  E_SDL_SET_PALETTE,
  E_SDL_CREATE_SURFACE,
  E_SDL_CREATE_TEXTURE,
  E_SDL_SET_RENDER_DRAW_COLOR,
  E_SDL_RENDER_CLEAR,
  E_COUNT
};

// Array of error messages
const std::string ERRORS[E_COUNT] {
  "ERROR: Invalid Image\n",
  "ERROR: Display was not initialized properly\n",
  "ERROR: Image dimensions exceed renderer limit\n",
  "ERROR: Failure in texture generation\n",
  "ERROR: Failure in SDL_RenderCopy()\n",
  "ERROR: Failure in SDL_Init()\n",
  "ERROR: Failure in SDL_CreateWindow()\n",
  "ERROR: Failure in SDL_CreateRenderer()\n",
  "ERROR: Failure in SDL_SetPaletteColors()\n",
  "ERROR: Failure in SDL_CreateRGBSurfaceWithFormatFrom()\n",
  "ERROR: Failure in SDL_CreateTextureFromSurface()\n",
  "ERROR: Failure in SDL_SetRenderDrawColor()\n",
  "ERROR: Failure in SDL_RenderClear()\n"
};

// Keywords for actions. Naming format: A_ACTION_NAME
enum Actions {
  A_CREATE_DISPLAY,
  A_DESTROY_DISPLAY,
  A_DRAW_IMAGE,
  A_COUNT
};

// Array of action messages
const std::string ACTIONS[A_COUNT] {
  "Display has been created\n",
  "Display has been destroyed\n",
  "Draw successfull\n"
};