set(
    CORE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/core.cmake
    ${CMAKE_CURRENT_LIST_DIR}/BBox.h
    ${CMAKE_CURRENT_LIST_DIR}/Exceptions.h
    ${CMAKE_CURRENT_LIST_DIR}/GameOfLife.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GameOfLife.h
    ${CMAKE_CURRENT_LIST_DIR}/Point.h   
)

source_group(core FILES ${CORE_SOURCES})
