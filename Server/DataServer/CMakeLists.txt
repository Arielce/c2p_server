PROJECT(dataserver)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES("/usr/include/mysql")
INCLUDE_DIRECTORIES("/usr/include/boost")
INCLUDE_DIRECTORIES("/usr/include/")

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
MESSAGE(STATUS "dir src:" +${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable -pthread")

LINK_DIRECTORIES("/home/chobits/workspace/lib")
LINK_DIRECTORIES("/usr/local/lib")
LINK_DIRECTORIES("/usr/local/mysql/lib")
LINK_DIRECTORIES("/usr/local/protobuf/lib")
#LINK_DIRECTORIES("/usr/lib/x86_64-linux-gnu/")

ADD_EXECUTABLE(dataserver ${DIR_SRCS})

TARGET_LINK_LIBRARIES(dataserver net)
TARGET_LINK_LIBRARIES(dataserver log4cplus)
TARGET_LINK_LIBRARIES(dataserver mysqlclient)
TARGET_LINK_LIBRARIES(dataserver boost_system)
TARGET_LINK_LIBRARIES(dataserver boost_thread)
TARGET_LINK_LIBRARIES(dataserver protobuf)
TARGET_LINK_LIBRARIES(dataserver TinyXml)
