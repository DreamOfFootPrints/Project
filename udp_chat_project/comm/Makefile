ROOT_PATH=$(shell pwd)
INCLUDE=-I../lib/include

LIB=#-L$(ROOT_PATH)/lib/lib

.PHONY:all
all:udp_data

udp_data:udp_data.o my_json.o
	g++ -o $@ $^ /home/xiaozhi/LinuxStudy/project_2/lib/lib/libjsoncpp.a

udp_data.o:udp_data.cpp
	g++ -c $< $(INCLUDE)

my_json.o:my_json.cpp
	g++ -c $< $(INCLUDE) -D _FAST_JSON_
.PHONY:clean
clean:
	rm -f udp_data my_json *.o
