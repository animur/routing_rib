CC=/usr/bin/g++
AR=/usr/bin/ar

ALL_UT=
# BIN_ARCH = -m32
BIN_ARCH = 

DSLIB_TOP = .
DSLIB_BLD_DIR = $(DSLIB_TOP)/bin/Debug

MODULE_NAME = rib
MODULE_OBJ_NAME = librib.a
MODULE_BLD_DIR = $(DSLIB_BLD_DIR)
MODULE_OBJ = $(MODULE_BLD_DIR)/$(MODULE_OBJ_NAME)
MODULE_OBJ_FILES = $(addprefix $(MODULE_BLD_DIR)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp )))

CFLAGS = -I./ -Wall -Werror -g -std=c++11 -D ALL_UT=$(ALL_UT) -pthread
LINKOPTS = 

Debug: all
all:  $(MODULE_BLD_DIR) $(MODULE_OBJ) testapp


$(MODULE_BLD_DIR):
	@echo $(MODULE_BLD_DIR)
	@mkdir -p $(MODULE_BLD_DIR)

$(MODULE_BLD_DIR)/%.o: %.cpp $(DEPS)
	$(CC) $(BIN_ARCH) -c -o $@ $< $(CFLAGS) 

$(MODULE_OBJ): $(MODULE_OBJ_FILES)
	$(AR) rcs $(MODULE_BLD_DIR)/$(MODULE_OBJ_NAME) $(MODULE_OBJ_FILES)

testapp:
	cd test; make;

clean:
	rm -rf $(MODULE_BLD_DIR)
	rm -f core.*
	cd test; make clean
