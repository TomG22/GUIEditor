cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

set(GLFW_BUILD_WAYLAND OFF)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

project(GUIEditor)


# Fetch the glfw dependency
include(FetchContent)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip
    URL_HASH SHA256=54efa829400f2a0537f742b2b3bdd74e437bb4f2f048e4b7d3c5557d11a611e6
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Populate(glfw)


add_executable(${PROJECT_NAME}
    src/main.cpp
    #src/Window.cpp
    #src/Camera.cpp
    #src/IndexBuffer.cpp
    #src/Mesh.cpp
    #src/Renderer.cpp
    #src/Shader.cpp
    #src/Texture.cpp
    #src/VertexArray.cpp
    #src/VertexBuffer.cpp

    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
    ${glfw_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${glfw_SOURCE_DIR}/lib-vc2022/glfw3.lib
    opengl32
)
