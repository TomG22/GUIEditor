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


add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Window.cpp
    src/Camera.cpp
    src/IndexBuffer.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp

    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/dependencies
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include

    ${glfw_SOURCE_DIR}/include
)


find_package(OpenGL REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    OpenGL::GL
)
