# Usage:
# make			# Compile all binary
# make run		# Run unix executable
# make clean	# Removes binaries, objects, and target

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic

# Finds source files
SOURCES := $(wildcard *.cpp)
# Performs string substitution on each source file
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))

# Target executable
TARGET := AMH-HuffmanTree

# Build rule unix executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

# Pattern rule that compiles every .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Convenience rule provided for quick execution
run: $(TARGET)
	@./$<

.PHONY: clean
clean:
	@echo "Cleaning..."
	$(RM) -f core *.o
	$(RM) $(TARGET)
