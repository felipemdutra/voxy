# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Isrc

# Libraries
LIBS = -lglfw -lGLEW -lGL -lwrapgl

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files (automatically find all .cpp files in src/)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BIN_DIR)/voxy

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean

