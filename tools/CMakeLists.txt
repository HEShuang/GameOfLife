add_executable(generator_board
    ${CORE_SOURCES}
    ${IO_SOURCES}
    generate_board.cpp
)

target_include_directories(generator_board PRIVATE
  ${GAMEOFLIFE_SOURCE_DIR}/core
  ${GAMEOFLIFE_SOURCE_DIR}/io
)

install(TARGETS generator_board
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
