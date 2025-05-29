cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

project(ListenerExample)

add_executable(ListenerExample
    main.cpp
    ListenerExample.cpp
)

set(ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../")

target_include_directories(ListenerExample PRIVATE
    "${ROOT}/include"
    "${ROOT}/dependencies/glad/include"
)

target_link_libraries(ListenerExample PRIVATE
    "${ROOT}/build/libGUIEditor.a"
    glfw dl GL
)
