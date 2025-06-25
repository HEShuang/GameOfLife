# Conway's Game of Life in C++

![CI & Test Status](https://github.com/HEShuang/GameOfLife/actions/workflows/ci.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/HEShuang/GameOfLife?include_prereleases)

[Documentation](https://heshuang.github.io/GameOfLife/)

A modern, cross-platform C++ implementation of John Conway's Game of Life, a zero-player cellular automaton where the evolution of the game is determined by its initial state.

For a detailed explanation of the rules, please see the [**Wikipedia article**](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## Features

* **Cross-Platform:** Compiles and runs on Windows, macOS, and Linux.
* **Infinite Board:** Simulates an infinite grid by only storing live cells, allowing patterns to grow without boundaries.
* **Automated CI/CD:** Every push and pull request is automatically built and tested. New version tags trigger a release with compiled binaries.
* **Unit Tested:** Core logic is verified with a suite of unit tests using the Google Test framework.
* **Modern C++ & CMake:** Built with C++17 standards and a clean, flexible CMake build system.

## 1. Getting Started (Installation)

The easiest way to get started is to download the latest pre-compiled executables for your operating system from **[Releases Page](https://github.com/HEShuang/GameOfLife/releases)**.

## 2. Building from Source

If you wish to compile the project yourself, simple build scripts are provided for your convenience.

### Prerequisites
* A C++17 compliant compiler (GCC, Clang, MSVC, etc).
* [CMake](https://cmake.org/download/) (version 3.16 or newer).

### Build Instructions
**On Linux or macOS:**
  ```bash
  # First, ensure the script is executable especially if you downloaded from zip(this is only needed once).
  chmod +x build.sh

  # Run the script to configure and build.
  ./build.sh
  ```
**On Windows:**
```batch
build.bat
```
Executables will be located in the `build/bin/` directory by default.

## 3. Usage

The project builds a command-line executable.

### `GameOfLife`
This program runs the main simulation. It loads an initial state from a file, runs a number of iterations, and saves the final state to a new file.

**Syntax:**
```bash
GameOfLife --input <filepath> --iterations <number> [--all]
```
**Example:**
```bash
./build/bin/GameOfLife --input samples/glider.txt --iterations 300 --all
```
This will run 300 generations with animation and save the final state to file glider_300.txt.

**Arguments:**
* --input <filepath>: (Required) Path to a board file. The format should use * for live cells and _ for dead cells.
* --iterations <number>: (Default: 100) The number of generations to simulate.
* --all: (Optional) If present, prints every generation to the console.
* --sleep: (Default:0) A positive integer in millisecond for sleep time between print of two generations.

## 4. Advanced Building & Testing
### `Custom Build Options`
The build scripts allow you to pass options directly to CMake to customize the build.
**Example:**
```bash
./build.sh --config Debug -B DebugBuild -DGAMEOFLIFE_BUILD_TESTS=OFF -G "Unix Makefiles"
```
### `Running the Unit Tests`
This project uses Google Test. Tests are built by default. To run them:
```bash
ctest --test-dir <path-to-build> --output-on-failure
```
### `Tool: generateBoard`
This utility creates a text file with a random pattern, which can be used as an input for the main application.

**Syntax:**
```bash
generateBoard <width> <height> <output_file> [live_chance]
```
**Example:**
```bash
./build/bin/generate_board 80 40 random_board.txt 0.3
```
* width, height: The dimensions of the random board.
* output_file: The file to save the board to.
* live_chance: (Optional) A probability from 0.0 to 1.0 for a cell to be alive. Default is 0.5.
