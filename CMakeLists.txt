cmake_minimum_required (VERSION 3.10)

project ("LDProtocol")

# Compile flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_C_FLAGS_RELEASE "/MT")
	set(CMAKE_C_FLAGS_DEBUG "/MTd")
	set(CMAKE_GENERATOR_TOOLSET "v141_xp")
else()
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static ")
	set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static ")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static ")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static ")
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static ")
endif()

add_subdirectory(third_party/openssl)
option( WITH_APPS "Build applications" Off )
add_subdirectory ("LDProtocol")
add_subdirectory ("OICQProtocol")