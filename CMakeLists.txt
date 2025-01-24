################################################################################
#
# @file      CMakeLists.txt
# @brief     Contains the build instructions for project files for the Junia
#            Editor
# @author    Max Hager
# @date      2024-04-14
# @copyright © Max Hager, 2024. All right reserved.
#
################################################################################

cmake_minimum_required(VERSION 3.26)

set(JUNIAEDITOR_NAME "JuniaEditor" CACHE STRING "")

project(${JUNIAEDITOR_NAME} VERSION 0.1.1 LANGUAGES CXX)

add_executable(${JUNIAEDITOR_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${JUNIAEDITOR_NAME})

set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set( BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin" )
set( DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dep" )

set_target_properties(${JUNIAEDITOR_NAME} PROPERTIES
	CXX_STANDARD_REQUIRED            ON
	CXX_STANDARD                     20
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${BIN_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}"
	RUNTIME_OUTPUT_DIRECTORY         "${BIN_DIR}"
	RUNTIME_OUTPUT_NAME_DEBUG        "${JUNIAEDITOR_NAME}"
	RUNTIME_OUTPUT_NAME_RELEASE      "${JUNIAEDITOR_NAME}"
	RUNTIME_OUTPUT_NAME              "${JUNIAEDITOR_NAME}"
)

target_compile_definitions(${JUNIAEDITOR_NAME} PRIVATE BUILD_JUNIAEDITOR)

# Junia
set( JUNIA_DLL_COPY_TARGET_DIR "${BIN_DIR}" )
add_subdirectory("${DEP_DIR}/Junia")
if(NOT ${JUNIA_FOUND})
	message(FATAL_ERROR "Junia could not be found!")
endif()

target_include_directories(${JUNIAEDITOR_NAME} PUBLIC
	"${SRC_DIR}"
	"${JUNIA_INCLUDE_DIR}"
)

target_link_libraries(${JUNIAEDITOR_NAME}
	"${JUNIA_LIBRARY}"
)

set(SRC_JUNIAEDITOR
	"${SRC_DIR}/Editor.hpp"
	"${SRC_DIR}/Editor.cpp"
)

target_sources(${JUNIAEDITOR_NAME} PRIVATE
	"${SRC_JUNIAEDITOR}"
)

source_group( "src" FILES ${SRC_JUNIAEDITOR} )

add_dependencies(${JUNIAEDITOR_NAME} Junia)
