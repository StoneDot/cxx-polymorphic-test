cmake_minimum_required(VERSION 2.8)

#set(CMAKE_VERBOSE_MAKEFILE 1)
set(RELEASE_FLAGS "-O3 -xAVX -inline-forceinline")
set(DEBUG_FLAGS "-ggdb -O0")
set(DIAGNOSE_FLAGS "-fsyntax-only -diag-enable=all")
set(ICPC_WARN_OPTIONS "-w2")
set(WARN_OPTIONS "-Wextra -Wfloat-equal -Wcomment")

# Application name
set(APPLICATION test)

# Set source files
set(SRC "test.cxx")

# Set comiler flags
set(ICPC_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS "-std=c++14")

# Set using libraries
set(LIBRARIES m)

# Compiler configuration
message("'${CMAKE_CXX_COMPILER}' command is used for compile.")
if(${CMAKE_CXX_COMPILER} MATCHES ".*icpc")
  # For icpc compiler

  set(WARN_OPTIONS "${ICPC_WARN_OPTIONS} ${WARN_OPTIONS}")
  set(CMAKE_CXX_FLAGS "${ICPC_CXX_FLAGS} ${CMAKE_CXX_FLAGS}")
elseif(${CMAKE_CXX_COMPILER} MATCHES ".*clang.*")
  # For clang compiler

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  # The above command does not work because of a distribution bug.
  # http://stackoverflow.com/questions/37096062/get-a-basic-c-program-to-compile-using-clang-on-ubuntu-16
  # So the next line command is used.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

# Set actual compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${WARN_OPTIONS} ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${RELASE_FLAGS}")
set(CMAKE_CXX_FLAGS_DIAGNOSE "${DIAGNOSE_FLAGS}")

# Comiple commands are exported as "compile_commands.json"
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Notify compiled sources
message("Compiled sources are as follows:")
message(${SRC})

# Specify creating binaries
add_executable(${APPLICATION} ${SRC})
