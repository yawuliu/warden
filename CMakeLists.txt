cmake_minimum_required(VERSION 3.27)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

project(warden)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DWIN32_LEAN_AND_MEAN)
if (WIN32 AND MSVC)
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
        "Graphic/gll/.h"
        "Graphic/gll/.cpp"
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

link_directories(${CMAKE_SOURCE_DIR}/build/Debug/)
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets OpenGL)
qt_standard_project_setup()
qt_add_executable(warden main.cpp external/glad/src/glad.c ${dir_src})
target_link_libraries(warden PRIVATE Qt6::Gui Qt6::Widgets Qt6::OpenGL)
set_target_properties(warden PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
add_custom_command(TARGET warden POST_BUILD
        COMMAND ${QT_INSTALL_DIR}/bin/windeployqt "$<TARGET_FILE:warden>"
)

target_include_directories(warden PRIVATE "/")
target_include_directories(warden PRIVATE "external/freetype-2.0.9/include")
target_include_directories(warden PRIVATE "external/")
#target_include_directories(warden PRIVATE "external/glew-2.1.0/include")
target_include_directories(warden PRIVATE "external/lua-5.1.3/src")
target_include_directories(warden PRIVATE "external/glad/include" )
#target_compile_options(warden PRIVATE "/Zc:offsetof-")
#include_directories(${OPENGL_INCLUDE_DIRS})
#add_subdirectory(${PROJECT_SOURCE_DIR}/external/glew-2.1.0/build/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/freetype-2.0.9)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/lua-5.1.3)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/expat-2.0.1)
#add_definitions(
#        -DGLEW_STATIC
#)
message("${CMAKE_SOURCE_DIR}/build/lib/Debug/")
# target_link_libraries(warden PUBLIC ${OPENGL_LIBRARIES})
# glew32d
#
target_link_libraries(warden PUBLIC freetype-2.0 ws2_32 lua-5.1 wsock32 expat-2.0)
target_compile_definitions(expat-2.0 PUBLIC -DXML_STATIC)
set_target_properties(warden PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
set_target_properties(freetype-2.0 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew PROPERTIES LIBRARY_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew PROPERTIES RUNTIME_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew_s PROPERTIES LIBRARY_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)
#set_target_properties(glew_s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
#        ${CMAKE_SOURCE_DIR}/build)