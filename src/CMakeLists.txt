project(ImageEditor)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}, ../include)
add_executable(
    ImageEditor
    main.cpp
    image.cpp
    buffer.cpp
    display.cpp
    process_user_commands.cpp
    helper_functions.cpp
    IP_change_brightness.cpp
    IP_extract_channel.cpp
    IP_histogram.cpp
    IP_monochrome.cpp
    IP_quantize.cpp
    IP_rotate.cpp   
)
target_link_libraries(ImageEditor ${SDL2_LIBRARIES})

