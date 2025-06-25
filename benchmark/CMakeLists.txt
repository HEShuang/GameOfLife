add_executable(benchmark
    ${CORE_SOURCES}
    ${IO_SOURCES}
    BenchMark.h
    BenchMark.cpp
    main.cpp
)

target_include_directories(benchmark PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

install(TARGETS benchmark
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
