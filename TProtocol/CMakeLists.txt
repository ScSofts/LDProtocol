cmake_minimum_required (VERSION 3.10)

add_executable(
    TProtocol
    index.cc
    wtlogin/build.cc
)
target_include_directories(TProtocol PUBLIC ${LDProtocol_SOURCE_DIR}/LDProtocol)
target_link_libraries(TProtocol LDProtocol ssl crypto)
