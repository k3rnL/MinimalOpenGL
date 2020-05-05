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
# add cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})


# get all source files
file(GLOB all_SRCS
        "include/*.h"
        "source/*.cpp"
        )

include_directories("include")

# add executable and addShader libraries
add_executable(minimalOpenGL ${all_SRCS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
find_package(glfw3 3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})

target_link_libraries(minimalOpenGL ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW3_LIBRARIES})

