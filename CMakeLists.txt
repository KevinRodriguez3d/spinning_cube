cmake_minimum_required(VERSION 3.16)
project(3d_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

# Use pkg-config to pull GLFW and its transitive deps (Wayland/X11, xkbcommon, etc.)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET glfw3)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/sources/*.cpp")
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    raylib
    PkgConfig::GLFW3
    m dl pthread                        # needed when raylib is static
)

