cmake_minimum_required(VERSION 3.15)
project(GeometryFigures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включить все предупреждения
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

# Поиск GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавить include директорию
include_directories(include)

# Основное приложение
add_executable(GeometryFigures 
    src/main.cpp
    src/geometry_functions.cpp
)
enable_testing()
# Тесты
add_executable(GeometryTests
    test/test_main.cpp
    test/test_point.cpp
    test/test_figures.cpp
    test/test_array.cpp
    # test/test_geometry_functions.cpp
    # src/geometry_functions.cpp  # Включаем реализацию функций
)

# Линковка тестов с GTest
target_link_libraries(GeometryTests GTest::gtest_main)

# Включение тестов в CTest
# include(GoogleTest)
add_test(NAME MyProjectTests COMMAND tests)
# gtest_discover_tests(GeometryTests)