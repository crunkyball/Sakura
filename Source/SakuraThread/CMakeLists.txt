file(GLOB sourceFiles
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

file(GLOB platformFiles
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${PLATFORM_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${PLATFORM_DIR}/*.h
)

add_library(SakuraThread ${sourceFiles} ${platformFiles})
