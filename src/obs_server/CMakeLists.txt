PROJECT(obs_server VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${LIBOBS_INCLUDE_DIR})
link_directories(${LIBOBS_DEPS_LIB_DIR} ${LIBOBS_LIB_DIR})

# Detect Architecture (Bitness)
IF( NOT CLANG_ANALYZE_CONFIG)
	math(EXPR BITS "8*${CMAKE_SIZEOF_VOID_P}")
ENDIF()

if(WIN32)
	set(LIBOBS_PLATFORM "windows64")
endif()

if (WIN32)
	set(PROJECT_LIBRARIES
		ipc
		${LIBOBS_LIB_LIST}
		dwmapi.lib
	)
	set(PROJECT_INCLUDE_PATHS
		"${CMAKE_SOURCE_DIR}/src/common"
		"${CMAKE_SOURCE_DIR}/src/ipc/include"
		"${PROJECT_SOURCE_DIR}/src"
		${LIBOBS_INCLUDE_DIR}
	)
endif ()

SET(osn-server_SOURCES
	"${CMAKE_SOURCE_DIR}/src/common/error.hpp"
	"${CMAKE_SOURCE_DIR}/src/common/obs-property.hpp"
	"${CMAKE_SOURCE_DIR}/src/common/obs-property.cpp"

	###### obs-studio-node ######
	"${PROJECT_SOURCE_DIR}/src/consts.h"
	"${PROJECT_SOURCE_DIR}/src/main.cpp"
	"${PROJECT_SOURCE_DIR}/src/shared.cpp"
	"${PROJECT_SOURCE_DIR}/src/shared.hpp"
	"${PROJECT_SOURCE_DIR}/src/utility.cpp"
	"${PROJECT_SOURCE_DIR}/src/utility.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-nodeobs.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-nodeobs.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-audio.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-audio.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-calldata.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-calldata.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-global.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-global.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-iencoder.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-iencoder.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-input.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-input.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-module.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-module.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-output.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-output.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-service.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-service.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-source.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-source.hpp"
	"${PROJECT_SOURCE_DIR}/src/osn-video.cpp"
	"${PROJECT_SOURCE_DIR}/src/osn-video.hpp"

	###### node-obs ######
	"${PROJECT_SOURCE_DIR}/src/nodeobs_api.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_api.h"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_audio_encoders.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_audio_encoders.h"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_autoconfig.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_autoconfig.h"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_configManager.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_configManager.hpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_service.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_service.h"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_settings.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_settings.h"
	"${PROJECT_SOURCE_DIR}/src/util-memory.cpp"
	"${PROJECT_SOURCE_DIR}/src/util-memory.h"
	
	###### callback-manager ######
	"${PROJECT_SOURCE_DIR}/src/callback-manager.cpp"
	"${PROJECT_SOURCE_DIR}/src/callback-manager.h"

	###### memory-manager ######
	"${PROJECT_SOURCE_DIR}/src/memory-manager.cpp"
	"${PROJECT_SOURCE_DIR}/src/memory-manager.h"
)

add_executable(
	${PROJECT_NAME}
	${osn-server_SOURCES}
)

if(WIN32)
	target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_PATHS})
	target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBRARIES})
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${dir}/Debug")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "obs_server_${BITS}_bits")

if(WIN32)
	set_target_properties(
		${PROJECT_NAME}
		PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION}
	)

	target_compile_definitions(${PROJECT_NAME} PRIVATE)
ENDIF()

IF(WIN32)
	target_compile_definitions(
		${PROJECT_NAME}
		PRIVATE
			WIN32_LEAN_AND_MEAN
			NOMINMAX
			UNICODE
			_UNICODE
	)
ENDIF()

set(PROGRAM_PERMISSIONS_DEFAULT
    OWNER_WRITE OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

install(TARGETS obs_server RUNTIME DESTINATION "${dir}" PERMISSIONS ${PROGRAM_PERMISSIONS_DEFAULT} COMPONENT Runtime)
IF(WIN32 AND NOT CLANG_ANALYZE_CONFIG)
	install(FILES $<TARGET_PDB_FILE:obs_server> DESTINATION "${dir}" OPTIONAL)
ENDIF()
install(DIRECTORY "${LIBOBS_MODULES_DIR}/" DESTINATION "${dir}/" USE_SOURCE_PERMISSIONS)


if (WIN32)
	install(
		DIRECTORY "${LIBOBS_LIB_DIR}/"
		DESTINATION "${dir}/" PATTERN "*.lib" EXCLUDE
	)
	install(
		DIRECTORY "${LIBOBS_DEPS_LIB_DIR}/"
		DESTINATION "${dir}/" PATTERN "*.lib" EXCLUDE
	)
endif ()
