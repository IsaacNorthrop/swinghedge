# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -g

# Source file
SOURCE = main.cpp request.cpp daily_matchups.cpp player_data.cpp

# Executable name
EXECUTABLE = swinghedge

# Default target
all: $(EXECUTABLE)

# Link source file to create the executable
$(EXECUTABLE): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o  $@ $^ -lcurl -lmyhtml

# Clean up build files
clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
