cmake_minimum_required(VERSION 2.8)
project(led-strip-server)

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "detected architecture: ${ARCHITECTURE}" )

set(CMAKE_CXX_STANDARD 14)

if( ${ARCHITECTURE} STREQUAL "x86_64" )
    # added -pthread
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
else()
    # added -pthread -lwiringPi
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lwiringPi")
endif()

file(GLOB_RECURSE SRC_C_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE SRC_CXX_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.cpp)
file(GLOB_RECURSE SRC_HEADERS ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*/*.h )

add_executable(${PROJECT_NAME}
        ${SRC_C_FILES} ${SRC_CXX_FILES} ${SRC_HEADERS})
        
install (TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin/)
install (DIRECTORY static/src DESTINATION $ENV{HOME}/.${PROJECT_NAME})
install (DIRECTORY config DESTINATION $ENV{HOME}/.${PROJECT_NAME})