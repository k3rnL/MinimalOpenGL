cmake_minimum_required(VERSION 3.10)

# Set a default build type if none was specified
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# create project
project(MinimalOpenGL)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# get all source files
file(GLOB all_SRCS
        "include/*.h"
        "source/*.cpp"
        )

include_directories("include")

# add executable and addShader libraries
add_executable(minimalOpenGL ${all_SRCS})

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

add_dependencies(minimalOpenGL OpenGL::OpenGL)
include_directories(${GLUT_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(minimalOpenGL OpenGL::OpenGL ${GLUT_LIBRARY} ${GLEW_LIBRARIES})

