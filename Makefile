CXX = clang++
CXXFLAGS = -std=c++11 -g3 -O0
BUILD_DIR = ./build/Debug
TARGET = $(BUILD_DIR)/outDebug
OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/tests.o $(BUILD_DIR)/PerformanceTest.o

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/PerformanceTest.o: PerformanceTest.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_FILES) $(TARGET)
