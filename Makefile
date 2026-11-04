CXX = clang++
# -O2 -Wall -Wextra -Wpedantic
CXXFLAGS = -std=c++23 
INCLUDES = -Iinclude
TARGET = bin/o.exe
SOURCE = src/main.cpp

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCE) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean