cmake_minimum_required(VERSION 3.5)
project(test.obs LANGUAGES CXX)

set(dir                            ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH         ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})

set(LIBOBS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/include/obs)
set(LIBOBS_MODULES_DIR ${CMAKE_SOURCE_DIR}/third_party/data/modules)
set(LIBOBS_LIB_DIR ${CMAKE_SOURCE_DIR}/third_party/lib/obs)
set(LIBOBS_DEPS_LIB_DIR ${CMAKE_SOURCE_DIR}/third_party/lib/obs_deps)
set(LIBOBS_LIB_LIST 
	${LIBOBS_LIB_DIR}/obs.lib
	${LIBOBS_LIB_DIR}/libobs-winrt.lib
	${LIBOBS_LIB_DIR}/libobs-d3d11.lib
	winmm 
	psapi 
	${LIBOBS_DEPS_LIB_DIR}/w32-pthreads.lib 
	${LIBOBS_DEPS_LIB_DIR}/caption.lib 
	${LIBOBS_DEPS_LIB_DIR}/jansson.lib 
	${LIBOBS_DEPS_LIB_DIR}/zlib.lib 
	${LIBOBS_DEPS_LIB_DIR}/avformat.lib 
	${LIBOBS_DEPS_LIB_DIR}/avutil.lib 
	${LIBOBS_DEPS_LIB_DIR}/swscale.lib 
	${LIBOBS_DEPS_LIB_DIR}/swresample.lib 
	${LIBOBS_DEPS_LIB_DIR}/avcodec.lib)

#include_directories(${LIBOBS_INCLUDE_DIR})
#link_directories(${LIBOBS_DEPS_LIB_DIR} ${LIBOBS_LIB_DIR})

#set(SOURCE ${PROJECT_SOURCE_DIR}/main.cpp)
#add_executable(${PROJECT_NAME} ${SOURCE})
#target_link_libraries(${PROJECT_NAME} ${LIBOBS_LIB_LIST})

add_subdirectory(ipc)
add_subdirectory(obs_server)
add_subdirectory(obs_client)