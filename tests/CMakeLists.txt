add_executable(runTests
    ${CORE_SOURCES}
    ${IO_SOURCES}
    test_bbox.cpp
    test_game.cpp
    test_generator.cpp
    test_serializer.cpp
)

target_include_directories(runTests PRIVATE
  ${PROJECT_SOURCE_DIR}/src
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
