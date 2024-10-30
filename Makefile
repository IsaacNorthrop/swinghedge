# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Source file
SOURCE = main.cpp request.cpp

# Executable name
EXECUTABLE = swinghedge

# Default target
all: $(EXECUTABLE)

# Link source file to create the executable
$(EXECUTABLE): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up build files
clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
