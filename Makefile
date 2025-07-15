CC = gcc
CFLAGS = -Wall -Wextra -Iheaders
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/dbview

SRC_FILES = main.c \
	   functions/fileOps.c \
	   functions/helper.c \
	   functions/employeeOps.c \
	   functions/dbutils.c \
	   functions/infos.c 

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@
	
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean