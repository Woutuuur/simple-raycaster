SRC = src/*.cpp
LIBS = -I ./include
CC = g++
LINKER_FLAGS = -lSDL2
BINARY_NAME = raycaster
all: $(SRC)
	$(CC) $(LIBS) $(SRC)  $(LINKER_FLAGS) -o $(BINARY_NAME)
