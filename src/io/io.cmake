set(
    IO_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/io.cmake
    ${CMAKE_CURRENT_LIST_DIR}/BoardGenerator.cpp    
    ${CMAKE_CURRENT_LIST_DIR}/BoardGenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/BoardSerializer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BoardSerializer.h
)

source_group(io FILES ${IO_SOURCES})
