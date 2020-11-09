set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(obs_client VERSION 1.0)

SET(NODEJS_URL "https://atom.io/download/atom-shell" CACHE STRING "Node.JS URL")
SET(NODEJS_NAME "iojs" CACHE STRING "Node.JS Name")
SET(NODEJS_VERSION "v6.1.11" CACHE STRING "Node.JS Version")

include(NodeJS)

nodejs_init()

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

SET(obs_client_SOURCES
	"${CMAKE_SOURCE_DIR}/src/common/error.hpp"
	"${CMAKE_SOURCE_DIR}/src/common/obs-property.hpp"
	"${CMAKE_SOURCE_DIR}/src/common/obs-property.cpp"

	"${PROJECT_SOURCE_DIR}/src/shared.cpp"
	"${PROJECT_SOURCE_DIR}/src/shared.hpp"
	"${PROJECT_SOURCE_DIR}/src/utility.cpp"
	"${PROJECT_SOURCE_DIR}/src/utility.hpp"
	"${PROJECT_SOURCE_DIR}/src/utility-v8.cpp"
	"${PROJECT_SOURCE_DIR}/src/utility-v8.hpp"
	"${PROJECT_SOURCE_DIR}/src/controller.cpp"
	"${PROJECT_SOURCE_DIR}/src/controller.hpp"
	"${PROJECT_SOURCE_DIR}/src/global.cpp"
	"${PROJECT_SOURCE_DIR}/src/global.hpp"
	"${PROJECT_SOURCE_DIR}/src/input.cpp"
	"${PROJECT_SOURCE_DIR}/src/input.hpp"
	"${PROJECT_SOURCE_DIR}/src/isource.cpp"
	"${PROJECT_SOURCE_DIR}/src/isource.hpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_api.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_api.hpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_service.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_service.hpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_settings.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_settings.hpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_autoconfig.cpp"
	"${PROJECT_SOURCE_DIR}/src/nodeobs_autoconfig.hpp"
	"${PROJECT_SOURCE_DIR}/src/main.cpp"
	"${PROJECT_SOURCE_DIR}/src/video.cpp"
	"${PROJECT_SOURCE_DIR}/src/video.hpp"
	"${PROJECT_SOURCE_DIR}/src/module.cpp"
	"${PROJECT_SOURCE_DIR}/src/module.hpp"
	"${PROJECT_SOURCE_DIR}/src/cache-manager.hpp"
	"${PROJECT_SOURCE_DIR}/src/cache-manager.cpp"

	###### callback-manager ######
	"${PROJECT_SOURCE_DIR}/src/callback-manager.cpp"
	"${PROJECT_SOURCE_DIR}/src/callback-manager.hpp"
)

add_nodejs_module(
	obs_client
	${obs_client_SOURCES}
)
#add_library(${PROJECT_NAME} SHARED ${obs_client_SOURCES} ${CMAKE_JS_SRC})

if(WIN32)
	target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_PATHS})
	target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBRARIES})
endif()

# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# Define NAPI_VERSION
add_definitions(-DNAPI_VERSION=4)
 
set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION}
	PREFIX "" SUFFIX ".node"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE BUILDING_NODE_EXTENSION)

if(WIN32)
	target_compile_definitions(
		${PROJECT_NAME}
		PRIVATE
			WIN32_LEAN_AND_MEAN
			NOMINMAX
			UNICODE
			_UNICODE
	)
endif()

IF(WIN32 AND NOT CLANG_ANALYZE_CONFIG)
	install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION ${dir}/ OPTIONAL)
ENDIF()
install(FILES "${PROJECT_SOURCE_DIR}/package.json" DESTINATION "${dir}/")

install(
	DIRECTORY "${PROJECT_SOURCE_DIR}/js/"
	DESTINATION "${dir}/"
	PATTERN "*.json" EXCLUDE
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "${dir}/" COMPONENT Runtime
	LIBRARY DESTINATION "${dir}/" COMPONENT Runtime
	ARCHIVE DESTINATION "${dir}/" COMPONENT Runtime	
)
