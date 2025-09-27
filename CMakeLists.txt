cmake_minimum_required(VERSION 3.16)
project(raylib_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raylib from Arch packages provides a CMake config file
find_package(raylib 5 REQUIRED)  # 5.x on Arch

# Collect sources (or list them explicitly instead of GLOB if you prefer)
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/sources/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_DESKTOP)

