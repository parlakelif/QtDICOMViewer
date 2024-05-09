cmake_minimum_required(VERSION 3.5)

project(QtDICOMViewer)

# Qt5 paketini bul
find_package(Qt5 REQUIRED COMPONENTS Widgets Xml)
find_package(OpenGL)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

# VTK paketini bul
find_package(VTK REQUIRED)

# GDCM paketini bul
find_package(GDCM REQUIRED)

# Derleme ayarları
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${GDCM_INCLUDE_DIRS})

# Add the VTK include directory to the project
find_package(VTK 9.3 REQUIRED)

set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
if (WIN32) 
    add_executable(QtDICOMViewer WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(QtDICOMViewer ${SOURCES})
endif()

# Add the target includes
target_include_directories(QtDICOMViewer PRIVATE ${FORMS_DIR})
target_include_directories(QtDICOMViewer PRIVATE ${INCLUDE_DIR})
target_include_directories(QtDICOMViewer PRIVATE ${SOURCE_DIR})


target_link_libraries( QtDICOMViewer Qt5::OpenGL)
target_link_libraries( QtDICOMViewer Qt5::Xml)
target_link_libraries( QtDICOMViewer Qt5::Widgets)
target_link_libraries( QtDICOMViewer ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries( QtDICOMViewer ${VTK_LIBRARIES})
target_link_libraries( QtDICOMViewer ${GDCM_LIBRARIES})