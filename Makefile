SRC = main.cpp game.cpp player.cpp ray.cpp
CC = g++
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lSDL2
BINARY_NAME = raycaster
all: $(SRC)
	$(CC) $(SRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BINARY_NAME)
