cmake_minimum_required(VERSION 3.0.0)
project(gogh VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(gogh src/gogh/gogh.cpp)
target_include_directories(gogh PUBLIC include)

set_property(TARGET gogh PROPERTY CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
