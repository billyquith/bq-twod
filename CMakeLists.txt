###############################
# BQ-Twod (2D utilities)
###############################

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

set(TWOD_VERSION_MAJOR 0)
set(TWOD_VERSION_MINOR 2)
set(TWOD_VERSION_PATCH 0)

project(bqtwod)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(src)
add_subdirectory(test)


