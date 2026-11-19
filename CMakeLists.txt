cmake_minimum_required(VERSION 3.20)
project(matrix_calculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix_lib
    src/matrix.cpp
)

target_include_directories(matrix_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(matrix_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(matrix_calculator src/main.cpp)
target_link_libraries(matrix_calculator PRIVATE matrix_lib)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(matrix_calculator PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
