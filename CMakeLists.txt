cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(name analysis)

project(${name} CXX)

# default built type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug Release"
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


execute_process(COMMAND root-config --libs OUTPUT_VARIABLE ROOTLIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(`root-config --cflags`)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14 -O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14 -O0 -Wall -Wextra -g")


add_executable(${name} ${name}.cc)
target_link_libraries(${name} ${ROOTLIBS})

#----------------------------------------------------------------------------
# Copy all input files to the build directory

set(FILES_INPUT
#  OutputLecture7.root
  )


foreach(_file ${FILES_INPUT})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_file}
    ${PROJECT_SOURCE_DIR}/build/${_file}
    COPYONLY
    )
endforeach()
