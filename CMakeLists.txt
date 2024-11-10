cmake_minimum_required(VERSION 3.27)
project(warden)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DWIN32_LEAN_AND_MEAN)
if (WIN32)
    add_compile_options(/wd4819)
endif ()

file(GLOB_RECURSE dir_src
        "Agile/*.h"
        "Agile/*.cpp"
        "Common/*.h"
        "Common/*.cpp"
        "NIpse/*.h"
        "NIpse/*.cpp"
        "NTempest/*.h"
        "NTempest/*.cpp"
        "Graphic/*.h"
        "Graphic/*.cpp"
        "Storm/*.h"
        "Storm/*.cpp"
        "include/*.h"
        "Anim/*.h"
        "Anim/*.cpp"
        "Services/*.h"
        "Services/*.cpp"
        "Scrn/*.h"
        "Scrn/*.cpp"
        "Glue/*.h"
        "Glue/*.cpp"
        "Event/*.h"
        "Event/*.cpp"
        "Net/*.h"
        "Net/*.cpp"
        "UI/*.h"
        "UI/*.cpp"
        "Game/*.h"
        "Game/*.cpp"
        "Sound/*.h"
        "Sound/*.cpp"
)
find_package(OpenGL REQUIRED)
link_directories(${CMAKE_SOURCE_DIR}/build/Debug/)
#link_directories(${CMAKE_SOURCE_DIR}build/externel/freetype-2.0.9/Debug/)
add_executable(warden main.cpp ${dir_src}
        Graphic/gll/GLLayerView.cpp
        Graphic/gll/WGLContext.cpp
        Graphic/gll/WGLContext.h)

target_include_directories(warden PRIVATE "/")
target_include_directories(warden PRIVATE "externel/freetype-2.0.9/include")
target_include_directories(warden PRIVATE "externel/")
target_include_directories(warden PRIVATE "externel/glew-2.1.0/include")
target_include_directories(warden PRIVATE "externel/lua-5.1.3/src")
target_compile_options(warden PRIVATE "/Zc:offsetof-")
include_directories(${OPENGL_INCLUDE_DIRS})
add_subdirectory(${PROJECT_SOURCE_DIR}/externel/glew-2.1.0/build/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/externel/freetype-2.0.9)
add_subdirectory(${PROJECT_SOURCE_DIR}/externel/lua-5.1.3)
add_subdirectory(${PROJECT_SOURCE_DIR}/externel/expat-2.0.1)
#add_definitions(
#        -DGLEW_STATIC
#)
message("${CMAKE_SOURCE_DIR}/build/lib/Debug/")
target_link_libraries(warden PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(warden PUBLIC glew32d freetype-2.0 lua-5.1 ws2_32 wsock32 expat-2.0)
target_compile_definitions(expat-2.0 PUBLIC -DXML_STATIC)
set_target_properties(warden PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(glew PROPERTIES LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(glew PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(glew PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew_s PROPERTIES LIBRARY_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew_s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)