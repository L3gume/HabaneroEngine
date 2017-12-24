cmake_minimum_required(VERSION 3.9)
project(VapeEngine)

set(CMAKE_CXX_STANDARD 17)

# multi-threaded build!
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CTEST_BUILD_FLAGS -j${N})
    set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(VapeEngine main.cpp common/loadShaders.cpp common/loadShaders.h common/CameraController.cpp common/CameraController.h input/InputManager.cpp input/InputManager.h input/InputListener.h input/InputMessage.h common/GameManager.cpp common/GameManager.h)

# Whenever a new directory is created, add it to the include path
include_directories(common)
include_directories(input)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(VapeEngine PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(VapeEngine PUBLIC DEBUG=0)
endif()

# gotta add that one to make sure we get all of OpenGL
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(VapeEngine ${OPENGL_gl_LIBRARY})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(VapeEngine ${GLEW_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(VapeEngine ${GLFW_LIBRARIES})
target_link_libraries(VapeEngine ${GLFW_STATIC_LIBRARIES})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
target_link_libraries(VapeEngine ${GLM_LIBRARIES})