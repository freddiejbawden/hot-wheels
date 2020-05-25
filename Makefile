# CC = clang

EXE = hotwheels
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
CC = g++
SRC = $(shell find . -name '*.cpp')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
STD=c++11

CFLAGS += -Wall
CPPFLAGS += -std=$(STD)
LDFLAGS=

.PHONY: all clean debug

all: $(EXE) 



$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


# debug: DEBUG = -DDEBUG
debug: DEBUG = -g -O0

debug: all

clean:
	$(RM) hotwheels