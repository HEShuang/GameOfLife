cmake_minimum_required(VERSION 3.16)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# --- BUILD Options---
option(GAMEOFLIFE_BUILD_TESTS "Build unit tests" ON)
option(GAMEOFLIFE_BUILD_TOOLS "Build tools" ON)

if(GAMEOFLIFE_BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/v1.17.0.zip
  ) # Keep update to the latest version.

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()
endif()

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




