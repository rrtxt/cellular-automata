CC = g++

CFLAGS = -Iinclude
LDFLAGS = -Llib
LIBS = -lraylib -lgdi32 -lwinmm

SRC = src/main.cpp
TARGET = build/game

RULES ?= 18

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)

run: $(TARGET)
	@echo "Run with rules: $(RULES)"
	./$(TARGET) $(RULES)

clean:
	rm -rf build
