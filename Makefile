# Ustawienia
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude
LDFLAGS = -lm

# Nazwa programu
TARGET = pso

# Katalogi
SRC_DIR = src
OBJ_DIR = obj

# Lista plików
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Główny cel
all: $(TARGET)

# Linkowanie (tworzenie pso)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Kompilacja (tworzenie plików .o w folderze obj)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tworzenie folderu obj
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Sprzątanie
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean