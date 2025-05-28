cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER c++)

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

set(GLFW_BUILD_WAYLAND OFF)
set(GLFW_BUILD_X11 ON)

project(GUIEditor)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Gui.cpp

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

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    PRIVATE
    glfw
    ${OPENGL_gl_LIBRARY}
    dl
    pthread
    X11
)
