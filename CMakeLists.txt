#the whole CMakeLists.txt for project ttiger
PROJECT(b5m)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# include directories
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/
  /usr/local/include
  /opt/local/include
)

# lib directories
LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/lib
  /usr/lib
  /usr/local/lib
  /opt/local/lib
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})


ADD_SUBDIRECTORY(Problem_A)
ADD_SUBDIRECTORY(Problem_B)
