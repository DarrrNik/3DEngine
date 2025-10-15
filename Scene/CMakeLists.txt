set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets 
    OpenGLWidgets
    OpenGL
)

file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(Scene SHARED 
    ${PROJECT_SOURCES}
)

target_link_libraries(Scene PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_custom_command(TARGET Scene POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Scene>
    ${WORKING_DIRECTORY}
)
