# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -g -Ijson/include -MMD -MP

# Directories
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = bin
DEP_DIR = build/deps

# Source files
SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SOURCE:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

# Executable name
EXECUTABLE = $(BIN_DIR)/swinghedge

# Default target
all: $(EXECUTABLE)

# Link object files to create the executable
$(EXECUTABLE): $(OBJ)
	@mkdir -p $(BIN_DIR)                # Ensure the bin directory exists
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcurl -lmyhtml

# Generate object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)                # Ensure the obj directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include the dependency files (if they exist)
-include $(DEP)

# Clean up build files
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(DEP_DIR)

.PHONY: all clean
