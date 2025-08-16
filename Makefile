# Force Clang++ regardless of system default
CXX := clang++
CXXFLAGS := -std=c++17 -I./include
LDFLAGS := -L./lib -lfmt

# Target and source
TARGET := app
SRC := main.cpp

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)
