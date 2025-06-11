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
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    URL_HASH SHA256=b5ec004b2712fd08e8861dc271428f048775200a2df719ccf575143ba749a3e9
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Populate(glfw)

add_subdirectory(${glfw_SOURCE_DIR})


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
    glfw
    opengl32
)
