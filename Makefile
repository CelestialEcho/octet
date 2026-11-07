CXX = clang++
# -O2 -Wall -Wextra -Wpedantic
CXXFLAGS = -std=c++23 -D_CRT_SECURE_NO_WARNINGS -Wno-deprecated
INCLUDES = -Iinclude
LIBRARIES = -Llib -lSDL3 -lopengl32
TARGET = bin/o.exe

# project source files
SOURCE = src/main.cpp

# dependencies' source files
SOURCE += include/glad/glad.c include/logc/log.c include/nanovg/nanovg.c
IMGUI = include/imgui/imgui.cpp include/imgui/imgui_demo.cpp include/imgui/imgui_draw.cpp include/imgui/imgui_tables.cpp include/imgui/imgui_widgets.cpp include/imgui/imgui_impl_sdl3.cpp include/imgui/imgui_impl_opengl3.cpp

all:
	@if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(IMGUI) $(SOURCE) $(LIBRARIES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	@if exist "$(TARGET)" del /Q "$(TARGET)"

.PHONY: all run clean
