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


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

find_package(Qt5Widgets REQUIRED)

QT5_WRAP_CPP(logging/logger.h)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(VapeEngine main.cpp common/loadShaders.cpp common/loadShaders.h common/CameraController.cpp common/CameraController.h input/InputManager.cpp input/InputManager.h input/InputListener.h input/InputMessage.h common/GameManager.cpp common/GameManager.h logging/logger.cpp logging/logger.h logging/logMessage.h logging/LogManager.cpp logging/LogManager.h)

# Whenever a new directory is created, add it to the include path
include_directories(common)
include_directories(input)
include_directories(logging)

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

include_directories(${Qt5Widgets_INCLUDE_DIRS})
target_link_libraries(VapeEngine Qt5::Widgets)