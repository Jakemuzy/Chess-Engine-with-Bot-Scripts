cmake_minimum_required(VERSION 3.18)

PROJECT(Chess)

set (CMAKE_CXX_STANDARD 17)
set(SDL3_DIR ${PROJECT_SOURCE_DIR}/include/SDL3/cmake)
set(SDL3_image_DIR ${PROJECT_SOURCE_DIR}/include/SDL3_image/cmake)


find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

file( GLOB SOURCES "src/*.cpp" "src/*.c")
link_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable( Chess ${SOURCES} )  # MAKE SURE TO ADD THE DLL TO THE EXECUTABLE FOLDER IN ORDER TO RUN

target_include_directories(
    Chess
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/libs
)
target_link_libraries(
    Chess
    PRIVATE 
        SDL3
        SDL3_image
)

