CC=/usr/bin/g++
AR=/usr/bin/ar

CFLAGS = -I./ -I../ -Wall -Werror -g -std=c++11 -D ALL_UT=$(ALL_UT) -pthread
LINKOPTS =

OBJ = rib_ut.bin
LIB = ../bin/Debug/librib.a

all: $(OBJ)

$(OBJ):
	$(CC) $(BIN_ARCH) -o $(OBJ) $(CFLAGS) rib_ut.cpp $(LIB)

clean:
	@rm -f   rib_ut.bin
	@rm -rf *.dSYM
	@rm -f core.*
