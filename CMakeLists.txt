cmake_minimum_required( VERSION 3.5.2 )
project( Castle_of_the_Winds-_Universal )

set( SOURCE_FILES main.cpp )
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

include_directories( "${PROJECT_SOURCE_DIR}" )
set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
#set( CMAKE_CXX_COMPILER_FLAGS "${CMAKE_CXX_COMPILER_FLAGS} -Wall -c -std=c++11" )
set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -F/Library/Frameworks -framework SDL2 -framework SDL2_image" )
add_executable( Castle_of_the_Winds-_Universal ${SOURCE_FILES} )
