cmake_minimum_required(VERSION 3.10)

project(GraphicalProgrammingCourse)

set(CMAKE_CXX_STANDARD 20)

# Fetch glfw
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(glfw)

set(
    SOURCES

    src/main.cpp

    src/GL/gl3w.c

    src/gp/Camera.cpp
    src/gp/Error.cpp
    src/gp/Program.cpp
    src/gp/RC.cpp
    src/gp/Shader.cpp
    src/gp/Window.cpp
)

set(
    HEADERS

    include/GL/gl3w.h
    include/GL/glcorearb.h

    include/gp/Other/GL.h

    include/gp/Camera.hpp
    include/gp/Drawable.hpp
    include/gp/Error.hpp
    include/gp/glObject.hpp
    include/gp/Program.hpp
    include/gp/RC.hpp
    include/gp/Shader.hpp   
    include/gp/Viewer.h
    include/gp/Window.hpp

    include/KHR/khrplatform.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE include)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 opengl32)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw GL)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

