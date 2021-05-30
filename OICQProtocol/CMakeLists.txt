cmake_minimum_required (VERSION 3.10)

add_executable(
    OICQProtocol
    index.cc
    protocol/tlv.cc
    protocol/device.cc
    protocol/userinfo.cc
)
target_include_directories(OICQProtocol PUBLIC ${LDProtocol_SOURCE_DIR}/LDProtocol)
target_link_libraries(OICQProtocol LDProtocol ssl crypto)
