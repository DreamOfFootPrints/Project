ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
DATA_POOL=$(ROOT_PATH)/data_pool
LIB=$(ROOT_PATH)/lib/include
PLUGIN=$(ROOT_PATH)/plugin
CONF=$(ROOT_PATH)/conf
WINDOW=$(ROOT_PATH)/window

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM)
INCLUDE+=-I$(DATA_POOL)
INCLUDE+=-I$(LIB)
INCLUDE+=-I$(WINDOW)

CC=g++
FLAGS=
LDFLAGS=-lpthread -lncurses#-static

SER_SRC=$(shell  ls -r $(SERVER) | grep -E '*.cpp')
SER_SRC+=$(shell ls -r $(COMM) | grep -E '*.cpp')
SER_SRC+=$(shell ls -r $(DATA_POOL) | grep -E '*.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell  ls -r $(CLIENT) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -r $(COMM) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -r $(WINDOW) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)


.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)  /home/xiaozhi/LinuxStudy/project_2/lib/lib/libjsoncpp.a
$(CLIENT_BIN):$(CLI_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)  /home/xiaozhi/LinuxStudy/project_2/lib/lib/libjsoncpp.a

%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE) 

%.o:$(DATA_POOL)/%.cpp
	@$(CC) -c $< $(INCLUDE)

%.o:$(WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE)

%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE)

%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE)

.PHONY:output
output:all
	@mkdir -p output/server
	@mkdir -p output/server/lib
	@mkdir -p output/server/log
	@mkdir -p output/server/conf
	@mkdir -p output/client
	@cp -f $(SERVER_BIN) output/server/
	@cp -f $(CLIENT_BIN) output/client/
	@cp -f $(PLUGIN)/server_ctl.sh output/server/
	@cp -f $(CONF)/server.conf  output/server/conf

.PHONY:debug
debug:	
	@echo $(SER_SRC)
	@echo $(SER_OBJ)









.PHONY:clean
clean:
	@rm -f *.o $(SERVER_BIN)  $(CLIENT_BIN)

