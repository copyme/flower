project(MeanCurvatureFlow)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)


include_directories(${PROJECT_HEADERS_DIR} ${PROJECT_HEADERS_DIR}/IO)

set(PROJECT_FILES 
  ${PROJECT_SRC_DIR}/IO/rply.c
  ${PROJECT_SRC_DIR}/IO/plydatareader.cpp
  ${PROJECT_SRC_DIR}/IO/plydatawriter.cpp
  ${PROJECT_SRC_DIR}/edgeextractor.cpp
  ${PROJECT_SRC_DIR}/meanflowfilter.cpp
  ${PROJECT_SRC_DIR}/mesh.cpp
  ${PROJECT_SRC_DIR}/Vector.cpp
)

set(TESTS
  ${PROJECT_TEST_DIR}/meshtests.cpp
  ${PROJECT_TEST_DIR}/vectortests.cpp
  ${PROJECT_TEST_DIR}/pointtests.cpp
)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${PROJECT_FILES})

#FIND_PACKAGE(CppUnit)
#if(CppUnit_FOUND)
#  add_definitions("-Wall -o")
#  include_directories( ${CppUnit_INCLUDE_DIRS} )
#  add_executable( testCases ${PROJECT_TEST_DIR}/testCases.cpp ${PROJECT_FILES} ${TESTS})
#  target_link_libraries( testCases ${CppUnit_LIBRARIES} )
#else()
#  MESSAGE("CPPUNIT not found!")
#endif()
