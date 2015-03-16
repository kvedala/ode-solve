cmake_minimum_required (VERSION 2.8)

project(ode-solve)

if(NOT CMAKE_COMPILER_IS_GNUCC)
	message(SEND_ERROR "Please compile using GCC toolchain.")
endif()

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -Wall -O2 -g")
#	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}")
#	set (COMPILE_FLAGS "${COMPILE_FLAGS} ${OPENMP_C_FLAGS}")
else (OPENMP_FOUND)
	message(SEND_ERROR "Your GCC does not support parallel API OpenMP.")
endif(OPENMP_FOUND)

configure_file (
	"src/config.h.in"
	"src/config.h"
)

file(GLOB_RECURSE ODE_SOURCES "src/*.c")
set(CMAKE_BINARY_DIR  bin)
add_executable(ode-solver ${ODE_SOURCES})

find_package(Doxygen)
if (DOXYGEN_FOUND)
	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE}
		${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	)
else (DOXYGEN_FOUND)
	message(WARNING "Did not find Doxygen. Not building documentation")
endif(DOXYGEN_FOUND)
