project(flower)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(PROJECT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_definitions( "-std=c++11" )

include_directories(${PROJECT_HEADERS_DIR} ${PROJECT_HEADERS_DIR}/IO ${PROJECT_HEADERS_DIR}/GUI ${PROJECT_LIB_DIR}/imgui)

set(PROJECT_FILES 
 ${PROJECT_SRC_DIR}/IO/rply.c
 ${PROJECT_SRC_DIR}/IO/plydatareader.cpp
 ${PROJECT_SRC_DIR}/IO/plydatawriter.cpp
 ${PROJECT_SRC_DIR}/edgeextractor.cpp
 ${PROJECT_SRC_DIR}/meanflowfilter.cpp
 ${PROJECT_SRC_DIR}/normalsfinder.cpp
 ${PROJECT_SRC_DIR}/GUI/camera.cpp
 ${PROJECT_SRC_DIR}/GUI/statemonitor.cpp
 ${PROJECT_SRC_DIR}/GUI/interface.cpp
 ${PROJECT_SRC_DIR}/GUI/input.cpp
 ${PROJECT_SRC_DIR}/mesh.cpp
 ${PROJECT_SRC_DIR}/GUI/flowrunner.cpp
 ${PROJECT_SRC_DIR}/GUI/glines.cpp
)

set(PROJECT_LIB
 ${PROJECT_LIB_DIR}/imgui/imguiRenderGL3.cpp
 ${PROJECT_LIB_DIR}/imgui/imgui.cpp
 ${PROJECT_LIB_DIR}/imgui/DroidSans.cpp
)

set(TESTS
  ${PROJECT_TEST_DIR}/meshtests.cpp
  ${PROJECT_TEST_DIR}/vectortests.cpp
  ${PROJECT_TEST_DIR}/pointtests.cpp
)


find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
else()
    message(ERROR " OPENGL not found!")
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

FIND_PACKAGE(GLEW REQUIRED)
if(GLEW_FOUND)
  include_directories( ${GLEW_INCLUDE_PATH} )
else()
  MESSAGE("GLEW not found!")
endif()


aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${PROJECT_LIB})

#FIND_PACKAGE(CppUnit)
#if(CppUnit_FOUND)
#  add_definitions("-Wall -o")
#  include_directories( ${CppUnit_INCLUDE_DIRS} )
#  add_executable( testCases ${PROJECT_TEST_DIR}/testCases.cpp ${PROJECT_FILES} ${TESTS})
#  target_link_libraries( testCases ${CppUnit_LIBRARIES} )
#else()
#  MESSAGE("CPPUNIT not found!")
#endif()
