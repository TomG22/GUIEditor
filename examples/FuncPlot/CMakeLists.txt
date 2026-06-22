set(CMAKE_BUILD_TYPE Debug)

add_executable(FuncPlot
    main.cpp
)

target_link_libraries(FuncPlot PRIVATE GUIEditor)

add_custom_command(TARGET FuncPlot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:FuncPlot>/res"
    VERBATIM
)

message(STATUS "Copying res from: ${CMAKE_SOURCE_DIR}/res")
