set(PROJECT_NAME LDProtocol)
cmake_minimum_required (VERSION 3.8)

LIST(APPEND SOURCES 
	"test/main.cc"
	"utils/cast.cc"
	"utils/hexstring.cc"
	"utils/bin.cc"
	"utils/exceptions.cc"
	"crypto/ecdh.cc"
	"crypto/md5.cc"
	"crypto/tea.cc"
	)
	
add_executable (
	${PROJECT_NAME}
	${SOURCES}
)

target_include_directories( ${PROJECT_NAME} PUBLIC ${openssl_SOURCE_DIR}/include)
target_link_libraries( ${PROJECT_NAME} ssl crypto)

SET_TARGET_PROPERTIES(LDProtocol PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../build")
