cmake_minimum_required(VERSION 3.10)
project(CityRoute LANGUAGES CXX)

# ---------------------------------------------------------------------------
# CityRoute - Smart Route Planner  (CS-214 DSA project)
# Owner: Member 1
#
# Rules of this build file (so nobody needs to edit it for new files):
#   * every .cpp inside src/ (except src/main.cpp) goes into one core library
#   * every tests/test_*.cpp becomes its own test program, run with ctest
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Benchmarks only make sense with optimisation, so default to Release.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

# ---- core library: all of src/ except main.cpp ----------------------------
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/src/main\\.cpp$")

set(HAS_CORE FALSE)
if(CORE_SOURCES)
  add_library(cityroute_core STATIC ${CORE_SOURCES})
  target_include_directories(cityroute_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
  set(HAS_CORE TRUE)
endif()

# ---- main program ----------------------------------------------------------
add_executable(cityroute src/main.cpp)
if(HAS_CORE)
  target_link_libraries(cityroute PRIVATE cityroute_core)
endif()

# ---- tests: one program per tests/test_*.cpp -------------------------------
enable_testing()
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/tests/test_*.cpp)
foreach(test_src ${TEST_SOURCES})
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  if(HAS_CORE)
    target_link_libraries(${test_name} PRIVATE cityroute_core)
  endif()
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
