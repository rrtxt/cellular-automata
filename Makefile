CC = gcc

CFLAGS = -Iinclude
LDFLAGS = -Llib
LIBS = -lraylib -lgdi32 -lwinmm

SRC = src/main.cpp
TARGET = build/game

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build
