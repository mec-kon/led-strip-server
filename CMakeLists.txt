cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project(led-strip-server)

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "detected architecture: ${ARCHITECTURE}" )

if( ${ARCHITECTURE} STREQUAL "x86_64" )
    # added -pthread
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
else()
    # added -pthread -lwiringPi on Rasperry Pi
    add_definitions(-DIS_RASPBERRY_PI)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lwiringPi")
endif()

# in order to use mqtt, libmosquittopp must be installed
option(USE_MQTT "use mqtt in project" ON)


file(GLOB_RECURSE SRC_CXX_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.cpp)
file(GLOB_RECURSE SRC_HEADERS ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*/*.h )

# in order to use mqtt, libmosquittopp must be installed
if(USE_MQTT)
    add_definitions(-DUSE_MQTT)
    message(STATUS "mqtt enabled")
else()
    list(REMOVE_ITEM SRC_CXX_FILES ${PROJECT_SOURCE_DIR}/src/communication/Mqtt.cpp)
    message(STATUS "mqtt disabled")
endif()

add_executable(${PROJECT_NAME}
        ${SRC_CXX_FILES} ${SRC_HEADERS})

# in order to use mqtt, libmosquittopp must be installed
if(USE_MQTT)
    target_link_libraries(${PROJECT_NAME} mosquittopp)
endif()

install (TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin/)
install (DIRECTORY static/src DESTINATION $ENV{HOME}/.${PROJECT_NAME})
install (DIRECTORY config DESTINATION $ENV{HOME}/.${PROJECT_NAME})
install(CODE "execute_process(COMMAND sudo chown -c $ENV{USER} $ENV{HOME}/.led-strip-server/src/deviceConfig.json)")
install(CODE "execute_process(COMMAND sudo chown -c $ENV{USER} $ENV{HOME}/.led-strip-server/config/websiteConfig.json)")
