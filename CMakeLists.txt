cmake_minimum_required(VERSION 3.10.0)
project(OpenGL-First-Project VERSION 0.1.0 LANGUAGES C CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Stb REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

#when you have a proper debugging add back WIN32 as a parameter
add_executable(${CMAKE_PROJECT_NAME} 
src/main.cpp
src/window.cpp
src/renderloop/rendercontext.cpp
src/error.cpp

)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
glfw
imgui::imgui
OpenGL::GL
glad::glad
glm::glm
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
${Stb_INCLUDE_DIR}
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic-errors -std=c++20)   

include(CTest)
enable_testing()

