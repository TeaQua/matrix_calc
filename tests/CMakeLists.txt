include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(matrix_tests test_matrix.cpp)
target_link_libraries(matrix_tests PRIVATE matrix_lib GTest::gtest_main)

target_compile_features(matrix_tests PRIVATE cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(matrix_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

gtest_discover_tests(matrix_tests)
