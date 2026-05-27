cmake_minimum_required(VERSION 3.10.0)
project(OpenGL-First-Project VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt CONFIG REQUIRED)
# find_package(glfw REQUIRED)
# find_package(OpenGL REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    fmt::fmt
)

include(CTest)
enable_testing()

