file(GLOB sourceFiles
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

file(GLOB platformFiles
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${RENDER_API_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${RENDER_API_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${PLATFORM_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${PLATFORM_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${RENDER_API_DIR}/${WINDOW_API_DIR}/SaWindow_Platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${RENDER_API_DIR}/${WINDOW_API_DIR}/SaWindow_Platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${RENDER_API_DIR}/${WINDOW_API_DIR}/SaViewport_Platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${RENDER_API_DIR}/${WINDOW_API_DIR}/SaViewport_Platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${SHADER_API_DIR}/SaEffect_Platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/${SHADER_API_DIR}/SaEffect_Platform.h
)

add_library(Sakura ${sourceFiles} ${platformFiles})

#Do the linking.

if(GLFW_FOUND)
    target_link_libraries(Sakura ${GLFW_LIBRARY})
endif()

if(OPENGL_FOUND)
    target_link_libraries(Sakura ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
endif()

if(CG_FOUND)
    target_link_libraries(Sakura ${CG_LIBRARY} ${CG_GL_LIBRARY})
endif()

if(GLEW_FOUND)
    target_link_libraries(Sakura ${GLEW_LIBRARIES})
endif()

if(SAKURA_RENDER_API STREQUAL "OpenGL ES")
    target_link_libraries(Sakura ${GLES_LIBRARY} ${EGL_LIBRARY})
endif()
