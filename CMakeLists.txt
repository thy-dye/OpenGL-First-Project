cmake_minimum_required(VERSION 3.10.0)
project(OpenGL-First-Project VERSION 0.1.0 LANGUAGES C CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Stb REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} WIN32 
    src/main.cpp
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

include(CTest)
enable_testing()

