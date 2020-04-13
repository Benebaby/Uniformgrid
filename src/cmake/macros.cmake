# Copies all runtime libraries to the binary directory
# Custom runtime libraries can be added to the PROJECT_RUNTIME_LIBRARIES variable
MACRO(COPY_RUNTIME_TO_BINARY)
	IF (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
   
		execute_process(COMMAND ${CMAKE_COMMAND}  -E make_directory
			${PROJECT_BINARY_DIR}/bin/
		)
		
		FOREACH(l ${PROJECT_RUNTIME_LIBRARIES})
			execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
			${l}
			${PROJECT_BINARY_DIR}/bin/
		)
		ENDFOREACH()
		
	
	ELSEIF (MSVC)
		
		FOREACH(l ${PROJECT_RUNTIME_LIBRARIES})
		
			FOREACH (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
				execute_process(COMMAND ${CMAKE_COMMAND}  -E make_directory
					${PROJECT_BINARY_DIR}/bin/${CONFIGURATION_TYPE}/
				)
				execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
					${l}
					${PROJECT_BINARY_DIR}/bin/${CONFIGURATION_TYPE}/
				)
			ENDFOREACH()
		
		ENDFOREACH()
		
	ENDIF ()
ENDMACRO()

MACRO(GENERATE_SUBDIRS result curdir bindir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(names "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
		IF (NOT ${child} MATCHES "\\..*")
			if(EXISTS ${curdir}/${child}/CMakeLists.txt)
				string(REPLACE " " "_" child ${child})
				SET(names ${names} ${child})
				message("BUILD FOR '${child}' GENERATED")
			endif()
		ENDIF()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${${result}} ${names})
  	FOREACH(n ${names})
  		add_subdirectory(${curdir}/${n} ${bindir}/${n})
  	ENDFOREACH()
ENDMACRO()

MACRO(FIND_SUBDIR_NAMES result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(names "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
		IF (NOT ${child} MATCHES "\\..*")
			if(EXISTS ${curdir}/${child}/CMakeLists.txt)
				string(REPLACE " " "_" child ${child})
				SET(names ${names} ${child})
			endif()
		ENDIF()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${${result}} ${names})
ENDMACRO()
MACRO(FIND_SUBDIRS result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(names "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
		IF (NOT ${child} MATCHES "\\..*")
			if(EXISTS ${curdir}/${child}/CMakeLists.txt)
				string(REPLACE " " "_" child ${child})
				SET(names ${names} ${curdir}/${child})
			endif()
		ENDIF()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${${result}} ${names})
ENDMACRO()


MACRO(VALIADATE_PATH result)
	set( pathlist "${ARGN}" )
	FOREACH(currentpath ${pathlist})
		IF(EXISTS ${currentpath})
			SET(${result} ${currentpath} CACHE PATH "Project specific path. Set manually if it was not found.")
			message("${result} FOUND AT ${currentpath}")
		ENDIF()
	ENDFOREACH()
	IF (NOT ${result})
		SET(${result} "PATH-NOTFOUND" CACHE PATH "Project specific path. Set manually if it was not found.")
		message("ERROR: ${result} NOT FOUND")
	ENDIF ()
ENDMACRO()

MACRO(READ_DEPENDENCIES result source_dir)
	set(${result} "")
	if(EXISTS ${source_dir}/dependencies.txt)
		FILE(READ ${source_dir}/dependencies.txt local_dependencies_raw)
		STRING(REGEX REPLACE "\n" ";" local_dependencies_raw "${local_dependencies_raw}")
	endif()
	
	FOREACH(dep ${local_dependencies_raw})
		IF(NOT "${dep}" MATCHES "^%")
			string(STRIP "${dep}" newDep)
			set(${result} ${${result}} ${newDep})
		ENDIF()
	ENDFOREACH()
ENDMACRO()
