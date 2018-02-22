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

#add_compile_options(-Wall -Wextra -Wpedantic)

# Whenever a new directory is created, add it to the include path
include_directories(core)
include_directories(common)
include_directories(input)
include_directories(logging)
include_directories(patterns)
include_directories(camera)
include_directories(components)
include_directories(render)
include_directories(imgui)
include_directories(editor)
include_directories(imgui/minizip)
include_directories(ecs)

file(GLOB_RECURSE ECS_DIR
            "ecs/*.h"
            "ecs/*.cpp"
        )

add_executable(VapeEngine main.cpp common/loadShaders.cpp common/loadShaders.h input/InputManager.cpp input/InputManager.h input/InputListener.h input/InputMessage.h core/Engine.cpp core/Engine.h logging/LogMessage.h logging/LogManager.cpp logging/LogManager.h core/GameObject.cpp core/GameObject.h common/util.h common/VapeGL.h render/PrimitiveShapes.h test_object/Player.cpp test_object/Player.h common/quatUtils.h render/util/objloader.cpp render/util/objloader.h render/util/texture.cpp render/util/texture.h imgui/imconfig.h  imgui/imgui_demo.cpp  imgui/imgui.h imgui/stb_rect_pack.h imgui/stb_truetype.h imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_internal.h imgui/stb_textedit.h imgui/imgui_impl_glfw_gl3.cpp imgui/imgui_impl_glfw_gl3.h common/gl3w.c common/gl3w.h common/glcorearb.h editor/Editor.cpp editor/Editor.h imgui/ImguiWindowsFileIO.cpp imgui/ImguiWindowsFileIO.hpp ${ECS_DIR} components/RenderableComponent.h systems/RenderSystem.cpp systems/RenderSystem.h components/TransformComponent.h components/CameraComponent.h systems/CameraSystem.cpp systems/CameraSystem.h components/ScriptComponent.h script/PlayerMovementScript.cpp script/PlayerMovementScript.h systems/ScriptSystem.cpp systems/ScriptSystem.h components/Script.cpp ecs/EntityConstructor.cpp ecs/EntityConstructor.h ecs/ConstructorFunctions.h ecs/ConstructorFunctions.cpp systems/TransformSystem.cpp systems/TransformSystem.h core/SceneManager.cpp core/SceneManager.h editor/EditorController.cpp editor/EditorController.h editor/EditorCamera.cpp editor/EditorCamera.h)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(VapeEngine PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(VapeEngine PUBLIC DEBUG=0)
endif()

target_compile_definitions(VapeEngine PUBLIC EDITOR=1)

find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(VapeEngine ${OPENGL_gl_LIBRARY})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(VapeEngine ${GLFW_LIBRARIES})
target_link_libraries(VapeEngine ${GLFW_STATIC_LIBRARIES})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
target_link_libraries(VapeEngine ${GLM_LIBRARIES})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(VapeEngine ${Boost_LIBRARIES})