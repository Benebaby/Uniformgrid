#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
# 

# glew root takes precedence
set(GLEW_ROOT_ENV $ENV{GLEW_ROOT})

set(OpenGL_ROOT_ENV $ENV{OpenGL_ROOT})

# For older cmake versions use root variable as additional search directory explicitly
IF(${CMAKE_VERSION} VERSION_LESS_EQUAL "3.12.0") 
	SET(GLEW_ADDITIONAL_SEARCH_DIRS ${GLEW_ROOT_ENV})
ENDIF()


if (WIN32)

	IF (MINGW)

		SET(GLEW_SEARCH_PATH_SUFFIX mingw)
		SET(GLEW_LIB_NAME libglew)
   
	ELSEIF (MSVC)
	
		# MSVC toolset suffix
		# Checks for version
		IF(MSVC_TOOLSET_VERSION EQUAL 140 OR MSVC_VERSION EQUAL 1900)
		
			SET(GLEW_SEARCH_PATH_SUFFIX "msvc140")
		ELSEIF(MSVC_TOOLSET_VERSION EQUAL 141 OR 
		(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS_EQUAL 1919) )
			SET(GLEW_SEARCH_PATH_SUFFIX "msvc141")
		ELSEIF(MSVC_TOOLSET_VERSION EQUAL 142 OR 
		(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS_EQUAL 1929) )
			SET(GLEW_SEARCH_PATH_SUFFIX "msvc141")
		ELSE()
			SET(GLEW_SEARCH_PATH_SUFFIX "") # good luck
		ENDIF()

		SET(GLEW_LIB_NAME glew)
		
		

	ENDIF()
	
	find_library(GLEW_LIBRARY_RELEASE 
		NAMES ${GLEW_LIB_NAME}
		PATHS
		${GLEW_ADDITIONAL_SEARCH_DIRS}
		PATH_SUFFIXES 
		${GLEW_SEARCH_PATH_SUFFIX}
		${GLEW_SEARCH_PATH_SUFFIX}/lib
	)
	find_library(GLEW_LIBRARY_DEBUG 
		NAMES "${GLEW_LIB_NAME}d"
		PATHS
		${GLEW_ADDITIONAL_SEARCH_DIRS}
		PATH_SUFFIXES 
		${GLEW_SEARCH_PATH_SUFFIX}
		${GLEW_SEARCH_PATH_SUFFIX}/lib
	) 

	FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h
		PATHS
		${GLEW_ADDITIONAL_SEARCH_DIRS}
		PATH_SUFFIXES ${GLEW_SEARCH_PATH_SUFFIX}/include
    )
	
	include(SelectLibraryConfigurations)
	select_library_configurations(GLEW)


	if(NOT GLEW_LIBRARY_RELEASE)
        set(GLEW_LIBRARY_RELEASE "GLEW_LIBRARY_RELEASE-NOTFOUND" CACHE FILEPATH "Path to a library.")
    endif()
    if(NOT GLEW_LIBRARY_DEBUG)
        set(GLEW_LIBRARY_DEBUG "GLEW_LIBRARY_DEBUG-NOTFOUND" CACHE FILEPATH "Path to a library.")
    endif()
	
    get_property(_isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if( GLEW_LIBRARY_DEBUG AND GLEW_LIBRARY_RELEASE AND
           NOT GLEW_LIBRARY_DEBUG STREQUAL GLEW_LIBRARY_RELEASE AND
           ( _isMultiConfig OR CMAKE_BUILD_TYPE ) )
        # if the generator is multi-config or if CMAKE_BUILD_TYPE is set for
        # single-config generators, set optimized and debug libraries
        set( GLEW_INTERFACE_LIBRARY "" )
        foreach( _libname IN LISTS GLEW_LIBRARY_RELEASE )
           list( APPEND GLEW_INTERFACE_LIBRARY $<$<CONFIG:RelWithDebInfo>:${_libname}>  )
           list( APPEND GLEW_INTERFACE_LIBRARY $<$<CONFIG:Release>:${_libname}>  )
           list( APPEND GLEW_INTERFACE_LIBRARY $<$<CONFIG:MinSizeRelease>:${_libname}>  )
        endforeach()
        foreach( _libname IN LISTS GLEW_LIBRARY_DEBUG )
            list( APPEND GLEW_INTERFACE_LIBRARY $<$<CONFIG:Debug>:${_libname}> )
        endforeach()
    elseif( GLEW_LIBRARY_RELEASE )
        set( GLEW_INTERFACE_LIBRARY ${GLEW_LIBRARY_RELEASE} )
    elseif( GLEW_LIBRARY_DEBUG )
        set( GLEW_INTERFACE_LIBRARY ${GLEW_LIBRARY_DEBUG} )
    else()
        set( GLEW_INTERFACE_LIBRARY "GLEW_LIBRARY-NOTFOUND")
    endif()
	
	
	
ELSEIF(APPLE)
	FIND_PATH( GLEW_INCLUDE_DIR GL/glew.h
	  PATHS ${GLEW_ROOT_ENV}/include/ ${OpenGL_ROOT_ENV}/include/ /usr/include /usr/local/include /opt/local/include
	)
	 
	FIND_LIBRARY( GLEW_LIBRARY
	  NAMES libGLEW.a
	  PATHS ${GLEW_ROOT_ENV}/lib ${OpenGL_ROOT_ENV}/lib /usr/lib /usr/local/lib /opt/local/lib
	)

	SET(GLEW_LIBRARIES ${GLEW_LIBRARY})

ELSE()
	FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h)
	FIND_LIBRARY(GLEW_LIBRARY
	NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)

	SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
ENDIF()
    

	
include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(GLEW
                                  REQUIRED_VARS GLEW_INCLUDE_DIR GLEW_LIBRARY)
set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
	
if(GLEW_FOUND AND NOT TARGET GLEW::glew)
    add_library(GLEW::glew INTERFACE IMPORTED)
	
	IF(NOT GLEW_INTERFACE_LIBRARY)
		SET(GLEW_INTERFACE_LIBRARY ${GLEW_LIBRARIES})
	ENDIF()
    set_target_properties(GLEW::glew PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}"
		INTERFACE_LINK_LIBRARIES "${GLEW_INTERFACE_LIBRARY}"
    )
endif()
