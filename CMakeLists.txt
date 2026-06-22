cmake_minimum_required(VERSION 3.10)

# Set the OGL packaging to modern packaging
set(OpenGL_GL_PREFERENCE "GLVND")

project(GUIEditor)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Set CMake to use static linking
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")


# Disable example programs by default
option(BUILD_EXAMPLES "Build example programs" OFF)


# Exposes compilation database to LSPs / linters / analysis tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)


# Remove extra GLFW overhead
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


include(FetchContent)

# Fetch the glfw dependency
FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    URL_HASH SHA256=b5ec004b2712fd08e8861dc271428f048775200a2df719ccf575143ba749a3e9
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(glfw)


# Fetch the freetype dependency
#FetchContent_Declare(
#    freetype
#    URL https://download.savannah.gnu.org/releases/freetype/freetype-2.13.3.tar.xz
#    URL_HASH SHA256=0550350666d427c74daeb85d5ac7bb353acba5f76956395995311a9c6f063289
#    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
#)

#FetchContent_MakeAvailable(freetype)


add_library(${PROJECT_NAME}
    src/GLDebug.cpp
    src/IndexBuffer.cpp
    src/Layout.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/Widget.cpp
    src/Window.cpp
    src/WindowManager.cpp

    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC
    include
    dependencies
    dependencies/glad/include

    ${glfw_SOURCE_DIR}/include

    #${freetype_SOURCE_DIR}/include
)


find_package(OpenGL REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    #freetype
    OpenGL::GL
)


target_compile_definitions(${PROJECT_NAME} PUBLIC
    PROJECT_ROOT_PATH="${CMAKE_SOURCE_DIR}"
)


if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
