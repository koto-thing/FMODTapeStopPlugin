CXX = g++
CXXFLAGS = -std=c++20 -I../src -I./include
BUILD_DIR = build

SRCS = ../src/ParameterGetCallbacks.cpp test_ParameterGetCallbacks.cpp
OBJS = $(BUILD_DIR)/ParameterGetCallbacks.o $(BUILD_DIR)/test_ParameterGetCallbacks.o

all: $(BUILD_DIR)/test_runner

$(BUILD_DIR)/test_runner: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/ParameterGetCallbacks.o: ../src/ParameterGetCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_ParameterGetCallbacks.o: test_ParameterGetCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
