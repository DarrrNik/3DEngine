find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS
    OpenGL
    OpenGLWidgets
)

include_directories(
    ./include/
)

file(GLOB_RECURSE PROJECT_SOURCES
    ./src/*.cpp
    ./include/*.hpp
)

add_library(Scene SHARED 
    ${PROJECT_SOURCES}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(Scene PRIVATE GLEW::GLEW glm::glm Qt6::OpenGL Qt6::OpenGLWidgets) #PUBLIC Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets)

add_custom_command(TARGET Scene POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Scene>
    ${WORKING_DIRECTORY}
)
