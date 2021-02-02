cmake_minimum_required(VERSION 3.10)
project(aapp)

add_definitions(-DETL_DEBUG)


include_directories(${UTPP_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/../../include)

set(SOURCE_FILES Asm.cpp)


add_executable(asm ${SOURCE_FILES})
target_include_directories(asm
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

set_property(TARGET asm PROPERTY CXX_STANDARD 17)
