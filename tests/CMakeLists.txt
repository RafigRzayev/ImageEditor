project(tests)
include_directories(../include)
add_executable(
    tests
    unit_tests.cpp
    test_IP_rotate.cpp 
    test_IP_change_brightness.cpp 
    test_IP_monochrome.cpp 
    test_IP_extract_channel.cpp 
    test_IP_quantize.cpp 
    ../src/image.cpp 
    ../src/helper_functions.cpp 
    ../src/IP_rotate.cpp 
    ../src/IP_change_brightness.cpp 
    ../src/IP_monochrome.cpp 
    ../src/IP_extract_channel.cpp 
    ../src/IP_quantize.cpp  
)


