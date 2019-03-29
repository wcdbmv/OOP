BIN_DIR = bin
INC_DIR = inc
OBJ_DIR = obj
SRC_DIR = src
APP_EXE = wm3dv.exec

RM := rm
MKDIR := mkdir
LOG_ERR := /dev/null

CC := gcc
CFLAGS := -I$(INC_DIR) -std=c11 -Wall -pedantic -Wextra -Werror
LDFLAGS := -lGL -lGLU -lglut -lm

SRC_EXT := c

SRCS := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.o, $(SRCS))
DIRS := $(OBJ_DIR) $(BIN_DIR)

.PHONY: all dir clean

all: dir $(BIN_DIR)/$(APP_EXE)

$(BIN_DIR)/$(APP_EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) $(CFLAGS) -o $@ -c $<

dir: $(DIRS)

$(DIRS):
	$(MKDIR) -p $@

clean:
	$(RM) -rf $(DIRS) 2>$(LOG_ERR)
