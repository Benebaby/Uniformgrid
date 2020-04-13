cmake_minimum_required (VERSION 3.1)
if(${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
    set(CMAKE_CXX_COMPILER_ARG1 "-std=c++11" CACHE STRING "C++ version for eclipse" FORCE)
    set(CMAKE_ECLIPSE_VERSION "4.4" CACHE STRING "Eclipse version" FORCE)
endif()

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

file(GLOB_RECURSE SOURCES *.cpp *.c *.cc)
file(GLOB_RECURSE HEADER *.h)
add_executable(${ProjectId} ${SOURCES} ${HEADER})

# To include library headers
# could be made more modular if each library had to put all headers in
# special include dir
include_directories(
    ${CMAKE_SOURCE_DIR}/libraries/
	${DEFAULT_INCLUDES}
)

add_definitions(-DRESOURCES_PATH="${RESOURCES_PATH}")
add_definitions(-DSHADERS_PATH="${SHADERS_PATH}")

# some functions (like printf) result in warnings in VS. Calm these warnings:
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DGLEW_STATIC)
# glew.h sets __gl_h_ which makes gl3.h think /gl.h (OpenGL 2) is included. Calm that warning:
add_definitions(-DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED)
# ... and really don't include GLU and GL(2)
add_definitions(-DGLEW_NO_GLU)
add_definitions(-DGLM_FORCE_RADIANS)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

READ_DEPENDENCIES(local_dependencies ${CMAKE_CURRENT_SOURCE_DIR})
IF( NOT "${local_dependencies}" STREQUAL "" )
	message("Executable ${ProjectId} dependencies:")
	FOREACH(dep ${local_dependencies})
		message("\t${dep}")
	ENDFOREACH()
ENDIF()

# link some local libs by default
SET(local_dependencies Tools stb ${local_dependencies})
list(REMOVE_DUPLICATES local_dependencies)
list(REMOVE_ITEM local_dependencies ${ProjectId})

# link with all dependencies
target_link_libraries(
    ${ProjectId}
	${local_dependencies}
	${DEFAULT_LIBS}
)

# Make install available only if the correct variable has been set
IF(${MAKE_INSTALLABLE})
	install(TARGETS ${ProjectId} DESTINATION bin)
ENDIF()


