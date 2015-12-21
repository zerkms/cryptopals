cmake_minimum_required (VERSION 2.8)
cmake_policy(SET CMP0015 NEW)
project (cryptopals)
set(CMAKE_BUILD_TYPE Release)

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

set(cryptopals_SRC ../src/conversions.cpp
                   ../src/encoding.cpp
                   ../src/encryption.cpp
                   ../src/utils.cpp
                   ../src/analysis.cpp)
                   
set(cryptopals_TEST ../tests/test_main.cpp
                    ../tests/test_set_1.cpp
                    ../tests/unit/analysis.cpp
                    ../tests/unit/encoding.cpp)

add_library(cryptopals SHARED ${cryptopals_SRC})

set(cryptopals_LIB libcryptopals.so)

include_directories(../../deps/catch-1.2.1
                    ../../src)
link_directories(../../build)

add_executable (cryptopals_tests ${cryptopals_TEST})

target_link_libraries(cryptopals_tests ${cryptopals_LIB})
