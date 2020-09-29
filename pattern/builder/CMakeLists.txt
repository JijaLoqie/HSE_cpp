cmake_minimum_required(VERSION 3.16)

project(BUILDER VERSION 0.0.1)

set(SOURCE builder.cpp)

add_executable(solve ${SOURCE})

set_target_properties(
	solve PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
