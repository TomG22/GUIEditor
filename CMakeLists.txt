cmake_minimum_required(VERSION 3.10)

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

# Fetch the freetype dependency
FetchContent_Declare(
    freetype
    URL https://download.savannah.gnu.org/releases/freetype/freetype-2.13.3.tar.xz
    URL_HASH SHA256=0550350666d427c74daeb85d5ac7bb353acba5f76956395995311a9c6f063289
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Populate(freetype)

add_subdirectory(${freetype_SOURCE_DIR})


add_executable(${PROJECT_NAME}
    src/main.cpp

    src/GLDebug.cpp
    src/IndexBuffer.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/Widget.cpp
    src/Window.cpp
    src/Rect.cpp

    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/dependencies
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include

    ${glfw_SOURCE_DIR}/include
    ${freetype_SOURCE_DIR}/include
)


find_package(OpenGL REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    freetype
    OpenGL::GL
)
