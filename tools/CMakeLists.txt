add_executable(generateBoard
    ${CORE_SOURCES}
    ${IO_SOURCES}
    main.cpp
)

target_include_directories(generateBoard PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

install(TARGETS generateBoard
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
