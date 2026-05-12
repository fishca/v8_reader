cmake_minimum_required(VERSION 3.20)

project(v8reader_core LANGUAGES CXX)

add_library(v8reader_core STATIC
	src/V8ReaderCore.cpp
	../src/V8File.cpp
	../src/utils.cpp
	../src/VersionFile.cpp
)

set_target_properties(v8reader_core PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

target_include_directories(v8reader_core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../src
		${CMAKE_CURRENT_SOURCE_DIR}/../src/zlib
)

if(MSVC)
	target_compile_options(v8reader_core PRIVATE /utf-8)
endif()

find_package(ZLIB QUIET)
if(ZLIB_FOUND)
	target_link_libraries(v8reader_core PUBLIC ZLIB::ZLIB)
else()
	message(WARNING "ZLIB was not found by CMake. v8reader_core can still be built as a static library, but final applications must link zlib.")
endif()

option(V8READER_BUILD_METADATA_LEGACY "Build legacy metadata model library (P1/P2 extraction stage, VCL-dependent)." OFF)
if(V8READER_BUILD_METADATA_LEGACY)
	include(cmake/V8ReaderMetadataLegacy.cmake)

	add_library(v8reader_metadata_legacy STATIC
		${V8READER_METADATA_LEGACY_SOURCES}
	)

	set_target_properties(v8reader_metadata_legacy PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)

	target_include_directories(v8reader_metadata_legacy
		PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_SOURCE_DIR}/../src
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/../src/zlib
	)

	if(MSVC)
		target_compile_options(v8reader_metadata_legacy PRIVATE /utf-8)
	endif()

	if(ZLIB_FOUND)
		target_link_libraries(v8reader_metadata_legacy PUBLIC ZLIB::ZLIB)
	endif()
endif()
