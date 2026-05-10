CXX = g++
CXXFLAGS = -std=c++20 -I../src -I../src/InterfaceAdapter -I../src/Framework -I../src/UseCase -I./include
BUILD_DIR = build

SRCS = ../src/InterfaceAdapter/ParameterGetCallbacks.cpp test_ParameterGetCallbacks.cpp
OBJS = $(BUILD_DIR)/ParameterGetCallbacks.o $(BUILD_DIR)/test_ParameterGetCallbacks.o

all: $(BUILD_DIR)/test_runner

$(BUILD_DIR)/test_runner: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/ParameterGetCallbacks.o: ../src/InterfaceAdapter/ParameterGetCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_ParameterGetCallbacks.o: test_ParameterGetCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
