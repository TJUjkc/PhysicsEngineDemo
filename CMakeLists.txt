cmake_minimum_required(VERSION 3.15)
project(SimplePhysicsEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW3
find_package(glfw3 REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/glad/glad.c
)

# Create executable
add_executable(SimplePhysicsEngine ${SOURCES})

# Include directories
target_include_directories(SimplePhysicsEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/glad
)

# Link libraries
target_link_libraries(SimplePhysicsEngine PRIVATE
    OpenGL::GL
    glfw
)

# Copy shaders to output directory
add_custom_command(TARGET SimplePhysicsEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:SimplePhysicsEngine>/shaders
)
