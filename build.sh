#!/usr/bin/env bash

# This script configures and builds the project for Linux/MacOS.
# By default:
# It builds the 'Release' configuration.
# It builds into 'build' subdirectory.
# It builds tests and tools as well.
#
# You can:
# Override build type with --config <build-type>.
# Override build path with -B <path-to-build>
# Turn off the build of tests and/or tools.
# You can add other CMake configuration options
#
# Example Usage:
#   ./build.sh
#   ./build.sh --config Debug
#   ./build.sh --config Debug -B DebugBuild -DGAMEOFLIFE_BUILD_TESTS=OFF
#   ./build.sh -G "Unix Makefiles"


# Stop the script if any command fails
set -e

BUILD_TYPE="Release"
BUILD_FOLDER="build"

# --- Parse Command-Line Arguments ---
# Loop through all arguments passed to the script
while [[ $# -gt 0 ]]; do
  key="$1"
  case $key in
    --config)
      BUILD_TYPE="$2" # next argument
      shift # past argument
      shift # past value
      ;;
    -B)
      BUILD_FOLDER="$2"
      shift # past argument
      shift # past value
      ;;
    *)
      # Any other argument is stored to be passed directly to CMake configuration
      CMAKE_ARGS+=("$1")
      shift # past argument
      ;;
  esac
done

echo "--- Configuring project (Build type: ${BUILD_TYPE}) ---"
cmake -S . -B ${BUILD_FOLDER} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} "${CMAKE_ARGS[@]}"

echo "--- Building project ---"
cmake --build ${BUILD_FOLDER} --config ${BUILD_TYPE}

echo ""
echo "Build complete!"
