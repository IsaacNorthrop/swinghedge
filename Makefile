# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -g -Ijson/include -MMD -MP

# Source files
SOURCE = main.cpp request.cpp daily_matchups.cpp player_data.cpp get_date.cpp
OBJ = $(SOURCE:.cpp=.o)
DEP = $(OBJ:.o=.d)

# Executable name
EXECUTABLE = swinghedge

# Default target
all: $(EXECUTABLE)

# Link object files to create the executable
$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcurl -lmyhtml

# Generate object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include the dependency files (if they exist)
-include $(DEP)

# Clean up build files
clean:
	rm -f $(EXECUTABLE) $(OBJ) $(DEP)

.PHONY: all clean
