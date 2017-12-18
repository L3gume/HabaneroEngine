cmake_minimum_required(VERSION 3.9)
project(Tutorial)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(Tutorial main.cpp common/loadShaders.cpp common/loadShaders.h)

# gotta add that one to make sure we get all of OpenGL
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(Tutorial ${OPENGL_gl_LIBRARY})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(Tutorial ${GLEW_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Tutorial ${GLFW_LIBRARIES})
target_link_libraries(Tutorial ${GLFW_STATIC_LIBRARIES})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
target_link_libraries(Tutorial ${GLM_LIBRARIES})