# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.10)

project ("LDProtocol")

#检测VS
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_C_FLAGS_RELEASE "/MT")
	set(CMAKE_C_FLAGS_DEBUG "/MTd")
	set(CMAKE_GENERATOR_TOOLSET "v141_xp")
else()
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	set(CMAKE_LINK_LIBRARY_FLAG "-static")
endif()


# 包含子项目。
add_subdirectory ("LDProtocol")
