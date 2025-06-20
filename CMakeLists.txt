cmake_minimum_required(VERSION 3.16)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- BUILD Options---
option(GAMEOFLIFE_BUILD_TESTS "Build unit tests" ON)
option(GAMEOFLIFE_BUILD_TOOLS "Build tools" ON)

set(GAMEOFLIFE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

include(src/app/app.cmake)
include(src/core/core.cmake)
include(src/io/io.cmake)

add_executable(GameOfLife 
    ${CORE_SOURCES}
    ${IO_SOURCES}
    ${APP_SOURCES}
)

target_include_directories(GameOfLife PRIVATE 
    ${GAMEOFLIFE_SOURCE_DIR}/core
    ${GAMEOFLIFE_SOURCE_DIR}/io
)

include(GNUInstallDirs)

install(TARGETS GameOfLife
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(GAMEOFLIFE_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(GAMEOFLIFE_BUILD_TOOLS)
  add_subdirectory(tools)
endif()




