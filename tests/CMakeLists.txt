include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.17.0.zip
) # Keep update to the latest version.

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests
    ${CORE_SOURCES}
    ${IO_SOURCES}
    test_bbox.cpp
    test_game.cpp
    test_generator.cpp
    test_serializer.cpp
)

target_include_directories(runTests PRIVATE
  ${GAMEOFLIFE_SOURCE_DIR}/core
  ${GAMEOFLIFE_SOURCE_DIR}/io
)

target_link_libraries(runTests PRIVATE
    GTest::gtest_main
)

# Enable CMake’s test runner to discover the tests included in the binary, using the GoogleTest CMake module
include(GoogleTest)
gtest_discover_tests(runTests)

install(TARGETS runTests
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
