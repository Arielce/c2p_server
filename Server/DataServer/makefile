#############################################################
# Created:	2013-08-12
# Author:	imovie@163.com
#
# make		Default, release mode.
# make debug	Debug mode.
# make install	Copy the compiled object to specify folder.
# make clean	Clean is clean, nothing else.
# make rebuild 	The same as clean and make.
#
#############################################################

#
# Judged by compiler, you can specify it.
#
CC      = g++

#
# Object name you want to make, you can change it as you wish.
#
PROG	= ./gameserver

#
# This is the path for source files, many times "." is enough.
# Though, you can fit with a absolute path.
#
SRC_DIR	= ./
#SUB_DIR = ./datastoreclient

#
# En, it's the suffix of our source file...
#
SFX	= .cpp

#
# Here, i want to get all source files having the suffix we have specified.
#
SRC	= $(foreach n, $(wildcard $(addprefix $(SRC_DIR)/*, $(SFX))), $(n))
#SRC	+= $(foreach n, $(wildcard $(addprefix $(SUB_DIR)/*, $(SFX))), $(n))

#
# Replace the suffix of SRC.
#
OBJ	= $(foreach n, $(SRC), $(patsubst %$(SFX), %.o, $(n)))

#
# Include files.
#
#INCLUDE = -I../ -I../include -I /usr/include/mysql -I /home/zhangsonglin/include
INCLUDE = -I../ -I/usr/local/include -I /usr/include/mysql -I /usr/include/boost -I /usr/include/

#
# Lib files.
#
#LIB = -L../lib -lTinyXml -llog4cplus -lNetUtils -lCoreCode -lpthread -lmysqlclient -lquickmail -L/home/zhangsonglin/lib -L /usr/local/mysql/lib
LIB = -L../lib -lTinyXml -lnet -llog4cplus -lmysqlclient -L/usr/local/lib -lboost_system -L /usr/local/mysql/lib -L/usr/local/protobuf/lib -lprotobuf
#
# Debug or Release?
#
MOD_DEBUG    = -D_DEBUG -g -c -Wall
MOD_RELEASE  = -DNDEBUG -c -Wall -O2


$(PROG):$(OBJ)
	echo $(SRC)
	$(CC) -o $(PROG) $(OBJ) $(LIB)
%.o:%$(SFX)
	$(CC) $(MOD_DEBUG) $(INCLUDE) $<


.PHONY : clean
clean :
	rm -f $(PROG) $(OBJ)

