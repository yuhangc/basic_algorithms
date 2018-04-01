cmake_minimum_required(VERSION 2.8)
project(math_alg)

# set c++ 11
if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

# compile all cpp files into executables
file(GLOB APP_SOURCES *.cpp)

foreach (source_file ${APP_SOURCES})
    get_filename_component( demo_name ${source_file} NAME_WE )
    add_executable( ${demo_name} ${source_file} )
endforeach (source_file ${APP_SOURCES})
