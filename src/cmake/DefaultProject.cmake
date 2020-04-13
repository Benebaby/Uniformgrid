include(${CMAKE_MODULE_PATH}/doxygen.cmake)
include(${CMAKE_MODULE_PATH}/macros.cmake)

# will be set to local if the variable USE_INSTALL_PATHS is set
IF(${MAKE_INSTALLABLE})
	message("INFO: Paths for resources and shaders will be set relative to execution directory. This is necessary for exporting/installing the projects.")
	set(RESOURCES_PATH resources)
	set(SHADERS_PATH shaders)	
ELSE()
	set(RESOURCES_PATH ${CMAKE_SOURCE_DIR}/../resources)
	set(SHADERS_PATH ${CMAKE_SOURCE_DIR}/shaders)
ENDIF()



IF(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.12.0") 
	# Allows find scripts to automatically search in environment variables LIBNAME_ROOT
	cmake_policy(SET CMP0074 NEW)
ENDIF()

# Determine if 64 Bit build
if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
	SET(BUILD_TYPE_64_BIT true)
endif()

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
   SET(BUILD_TYPE_64_BIT true)
endif()

if(CMAKE_CL_64)
   SET(BUILD_TYPE_64_BIT true)
endif()


IF(BUILD_TYPE_64_BIT)
	  set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
ENDIF()



find_package(OpenGL3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(GLM REQUIRED)

set(DEFAULT_INCLUDES
	${CMAKE_SOURCE_DIR}/libraries/Tools/include
	${CMAKE_SOURCE_DIR}/libraries/stb/include
)

set(DEFAULT_LIBS
	${OpenGL3_LIBRARIES}
	GLFW3::glfw3
	Assimp::Assimp
	GLM::glm
	GLEW::glew
	OpenGL3::OpenGL3
	Tools
	stb
)
IF (WIN32)
	set(DEFAULT_LIBS
	${DEFAULT_LIBS}
	opengl32
	)
	
ENDIF()

if("${CMAKE_SYSTEM}" MATCHES "Linux")
	find_package(X11)
	set(DEFAULT_LIBS ${DEFAULT_LIBS} ${CMAKE_DL_LIBS} ${X11_LIBRARIES} Xrandr Xxf86vm Xi pthread)
endif()


## Old variable
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
link_directories(${LIBRARY_OUTPUT_PATH})
#
#

FIND_SUBDIR_NAMES(ALL_LIBRARIES ${CMAKE_SOURCE_DIR}/libraries)
GENERATE_SUBDIRS(ALL_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/libraries ${PROJECT_BINARY_DIR}/libraries)


#
## Old variable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

GENERATE_SUBDIRS(ALL_EXECUTABLES ${CMAKE_SOURCE_DIR}/executables ${PROJECT_BINARY_DIR}/executables)

if(EXISTS ${CMAKE_SOURCE_DIR}/shaders)
	add_subdirectory(${CMAKE_SOURCE_DIR}/shaders)
endif()

COPY_RUNTIME_TO_BINARY()

# Make install available only if the correct variable has been set
IF(${MAKE_INSTALLABLE})
	# copy shaders into destination
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/shaders DESTINATION bin
		PATTERN "CMakeLists.txt" EXCLUDE)
	# copy resources
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/../../resources DESTINATION bin)
	# copy all found runtime libraries
	install(FILES ${PROJECT_RUNTIME_LIBRARIES} DESTINATION bin)
ENDIF()