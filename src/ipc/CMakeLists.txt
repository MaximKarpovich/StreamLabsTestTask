cmake_minimum_required(VERSION 3.5)
project(ipc)

cmake_minimum_required(VERSION 3.1.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect Architecture (Bitness)
math(EXPR BITS "8*${CMAKE_SIZEOF_VOID_P}")

# Windows
IF(WIN32)
	# Detect Visual Studio Version
	STRING(REGEX REPLACE "^Visual Studio [0-9]+ ([0-9]+)(| Win64)$" "\\1" VS_YEAR "${CMAKE_GENERATOR}")
ENDIF()

# File List
SET(ipc_SOURCES
	"${PROJECT_SOURCE_DIR}/source/ipc.cpp"
	"${PROJECT_SOURCE_DIR}/include/ipc.hpp"
	"${PROJECT_SOURCE_DIR}/source/ipc-class.cpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-class.hpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-client.hpp"
	"${PROJECT_SOURCE_DIR}/source/ipc-function.cpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-function.hpp"
	"${PROJECT_SOURCE_DIR}/source/ipc-server.cpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-server.hpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-server-instance.hpp"
	"${PROJECT_SOURCE_DIR}/source/ipc-value.cpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-value.hpp"
	"${PROJECT_SOURCE_DIR}/include/util.h"
	"${PROJECT_SOURCE_DIR}/include/waitable.hpp"
	"${PROJECT_SOURCE_DIR}/include/tags.hpp"
	"${PROJECT_SOURCE_DIR}/include/semaphore.hpp"
	"${PROJECT_SOURCE_DIR}/include/error.hpp"
	"${PROJECT_SOURCE_DIR}/include/async_op.hpp"
	"${PROJECT_SOURCE_DIR}/source/async_op.cpp"
	"${PROJECT_SOURCE_DIR}/include/ipc-socket.hpp"
)
IF (WIN32)
	SET(ipc_SOURCES_WINDOWS
		"${PROJECT_SOURCE_DIR}/source/windows/utility.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/utility.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/semaphore.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/semaphore.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/overlapped.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/overlapped.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/async_request.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/async_request.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/waitable.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/ipc-client-win.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/ipc-client-win.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/ipc-server-instance-win.cpp"
		"${PROJECT_SOURCE_DIR}/source/windows/ipc-server-instance-win.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/ipc-socket-win.hpp"
		"${PROJECT_SOURCE_DIR}/source/windows/ipc-socket-win.cpp"
	)
ENDIF()


IF(WIN32)
	# Windows
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)

	# windows.h
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DNOGPICAPMASKS)
	add_definitions(-DNOVIRTUALKEYCODES)
	add_definitions(-DNOWINMESSAGES)
	add_definitions(-DNOWINSTYLES)
	add_definitions(-DNOSYSMETRICS)
	add_definitions(-DNOMENUS)
	add_definitions(-DNOICONS)
	add_definitions(-DNOKEYSTATES)
	add_definitions(-DNOSYSCOMMANDS)
	add_definitions(-DNORASTEROPS)
	add_definitions(-DNOSHOWWINDOW)
	add_definitions(-DNOATOM)
	add_definitions(-DNOCLIPBOARD)
	add_definitions(-DNOCOLOR)
	add_definitions(-DNOCTLMGR)
	add_definitions(-DNODRAWTEXT)
	add_definitions(-DNOGDI)
	add_definitions(-DNOKERNEL)
	#add_definitions(-DNOUSER)
	add_definitions(-DNONLS)
	add_definitions(-DNOMB)
	add_definitions(-DNOMEMMGR)
	add_definitions(-DNOMETAFILE)
	add_definitions(-DNOMINMAX)
	#add_definitions(-DNOMSG)
	add_definitions(-DNOOPENFILE)
	add_definitions(-DNOSCROLL)
	add_definitions(-DNOSERVICE)
	add_definitions(-DNOSOUND)
	add_definitions(-DNOTEXTMETRIC)
	add_definitions(-DNOWH)
	add_definitions(-DNOWINOFFSETS)
	add_definitions(-DNOCOMM)
	add_definitions(-DNOKANJI)
	add_definitions(-DNOHELP)
	add_definitions(-DNOPROFILER)
	add_definitions(-DNODEFERWINDOWPOS)
	add_definitions(-DNOMCX)
	
	LIST(
		APPEND
		ipc_SOURCES
		${ipc_SOURCES_WINDOWS}
	)
ENDIF()

# Directories
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/source
	${PROJECT_SOURCE_DIR}/include
)
LINK_DIRECTORIES(
)

# Building
ADD_LIBRARY(${PROJECT_NAME} STATIC
	${ipc_SOURCES}
)

# Linking
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
	${ipc_LIBRARIES}
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "${dir}/" COMPONENT Runtime
	LIBRARY DESTINATION "${dir}/" COMPONENT Runtime
	ARCHIVE DESTINATION "${dir}/" COMPONENT Runtime	
)