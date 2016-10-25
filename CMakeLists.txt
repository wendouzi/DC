cmake_minimum_required(VERSION 3.0)
PROJECT(DISEASECONTROL)
set(CMAKE_BUILD_TYPE Release)
set(WORKSPACE ${PROJECT_SOURCE_DIR}/..)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake
                      ${WORKSPACE}/thirdparty/cmake/modules
                      ${CMAKE_MODULE_PATH})
include(cmake/thirdparty.cmake)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(module)

