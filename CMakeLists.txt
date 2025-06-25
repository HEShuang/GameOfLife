cmake_minimum_required(VERSION 3.16)

# For DOWNLOAD_EXTRACT_TIMESTAMP option to be true
cmake_policy(SET CMP0135 NEW)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# This ensures executables will be in the same 'bin' directory, especially for multi-config generators like MSVC
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${EXECUTABLE_OUTPUT_PATH})


# --- BUILD Options---
option(GAMEOFLIFE_BUILD_TESTS "Build unit tests" ON)
option(GAMEOFLIFE_BUILD_TOOLS "Build tools" ON)
option(GAMEOFLIFE_BUILD_BENCHMARK "Build benchmark" ON)

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

include(src/app/app.cmake)
include(src/core/core.cmake)
include(src/io/io.cmake)
include(src/render/render.cmake)

add_executable(GameOfLife 
    ${CORE_SOURCES}
    ${IO_SOURCES}
    ${RENDER_SOURCES}
    ${APP_SOURCES}
)

target_include_directories(GameOfLife PRIVATE
    ${PROJECT_SOURCE_DIR}/src
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

if(GAMEOFLIFE_BUILD_BENCHMARK)
  add_subdirectory(benchmark)
endif()


