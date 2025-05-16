cmake_minimum_required(VERSION 3.27)
project(warden)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DWIN32_LEAN_AND_MEAN)
if (WIN32 AND MSVC)
    add_compile_options(/wd4819)
endif ()

# Set up vcpkg
# https://blog.csdn.net/weixin_44084452/article/details/141273813
set(VCPKG_ROOT "C:/Users/liuyawu/.vcpkg-clion/vcpkg")
set(VCPKG_TARGET_TRIPLET x64-windows) # Adjust for your system
#set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
#message(WARNING "${CMAKE_TOOLCHAIN_FILE}")
set(CMAKE_PREFIX_PATH "C:/Users/liuyawu/.vcpkg-clion/vcpkg/installed/x64-windows")

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
# find_package(OpenGL REQUIRED)
link_directories(${CMAKE_SOURCE_DIR}/build/Debug/)
#find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

#link_directories(${CMAKE_SOURCE_DIR}build/external/freetype-2.0.9/Debug/)
add_executable(warden main.cpp external/glad/src/glad.c ${dir_src})
#target_include_directories(warden PRIVATE Qt5::Core Qt5::Widgets Qt5::OpenGL)
#target_link_libraries(warden PRIVATE Qt5::Core Qt5::Widgets Qt5::OpenGL)

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
target_link_libraries(warden PUBLIC freetype-2.0 lua-5.1 ws2_32 wsock32 expat-2.0)
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