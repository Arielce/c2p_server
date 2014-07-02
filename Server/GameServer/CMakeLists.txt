PROJECT(gameserver)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES("/usr/include/mysql")
INCLUDE_DIRECTORIES("/usr/include/boost")
INCLUDE_DIRECTORIES("/usr/include/")

ADD_SUBDIRECTORY(redis)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
MESSAGE(STATUS "dir src:" +${DIR_SRCS})
#ADD_EXECUTABLE(gameserver ${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable -pthread")
SET( CMAKE_BUILD_TYPE Debug )


LINK_DIRECTORIES("/home/chobits/workspace/lib")
LINK_DIRECTORIES("/usr/local/lib")
LINK_DIRECTORIES("/usr/local/mysql/lib")
LINK_DIRECTORIES("/usr/local/protobuf/lib")
#LINK_DIRECTORIES("/usr/lib/x86_64-linux-gnu/")

ADD_EXECUTABLE(gameserver ${DIR_SRCS})

TARGET_LINK_LIBRARIES(gameserver redis)
TARGET_LINK_LIBRARIES(gameserver net)
TARGET_LINK_LIBRARIES(gameserver log4cplus)
TARGET_LINK_LIBRARIES(gameserver mysqlclient)
TARGET_LINK_LIBRARIES(gameserver boost_system)
TARGET_LINK_LIBRARIES(gameserver boost_thread)
TARGET_LINK_LIBRARIES(gameserver protobuf)
TARGET_LINK_LIBRARIES(gameserver TinyXml)

#ADD_EXECUTABLE(gameserver ${DIR_SRCS})
