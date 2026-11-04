CXX = clang++
# -O2 -Wall -Wextra -Wpedantic
CXXFLAGS = -std=c++23 
INCLUDES = -Iinclude
LIBRARIES = -Llib -lSDL3 -lopengl32
TARGET = bin/o.exe
SOURCE = src/main.cpp include/glad/glad.c

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBRARIES) $(SOURCE) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean