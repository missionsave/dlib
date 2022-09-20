 
CFLAGS = -w -Os -std=c++17  
INC = -I. -Ieasylzma/src -DGLEW_STATIC 
OUT_DIR=.lib

ifeq ($(OS),Windows_NT)
    uname_S := Windows
else
    uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Windows)
	# -DWIN32 -D_WIN32
	OUT_FILE_NAME = libeasylzmaw.a
	OBJ_DIR=.objw64
endif
ifeq ($(uname_S), Linux)
	OUT_FILE_NAME = libeasylzmal.a
	OBJ_DIR=.objl64
endif

OBJSCPP= $(patsubst %.cpp,$(OBJ_DIR)/%.cpp.o,$(wildcard *.cpp))
OBJSC= $(patsubst %.c,$(OBJ_DIR)/%.c.o,$(wildcard *.c))

all: dirmake $(OUT_FILE_NAME)

# Enumerating of every *.cpp as *.o and using that as dependency
$(OUT_FILE_NAME):  $(OBJSCPP) $(OBJSC)
	ar -r -o $(OUT_DIR)/$@ $^

#Compiling every *.cpp to *.o
$(OBJ_DIR)/%.cpp.o: %.cpp 
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<
$(OBJ_DIR)/%.c.o: %.c 
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<
	
dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/$(OUT_FILE_NAME)

rebuild: clean build

.PHONY: all remake clean cleaner