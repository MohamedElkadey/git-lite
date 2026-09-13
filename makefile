CXX = g++

TARGET = app

SRC_DIR = src
BUILD_DIR = build

CXXFLAGS = -Wall -Wextra -std=c++20 -MMD -MP 
LDLIBS = -lcrypto -lz
# Find all cpp files
SRC = $(shell find $(SRC_DIR) -name "*.cpp")

# Convert src/file.cpp -> build/file.o
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dependency files
DEP = $(OBJ:.o=.d)


# Default target
all: $(TARGET)


# Link object files
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDLIBS)


# Compile cpp -> object
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@


# Include generated dependency files
-include $(DEP)


# Remove generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)


# Rebuild everything
rebuild: clean all


.PHONY: all clean rebuild
