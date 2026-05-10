CXX = g++
CXXFLAGS = -std=c++20 -I../src -I../src/InterfaceAdapter -I../src/Framework -I../src/UseCase -I./include
BUILD_DIR = build

all: $(BUILD_DIR)/test_ParameterGetCallbacks $(BUILD_DIR)/test_DSPCallbacks

$(BUILD_DIR)/test_ParameterGetCallbacks: $(BUILD_DIR)/test_ParameterGetCallbacks.o $(BUILD_DIR)/ParameterGetCallbacks.o $(BUILD_DIR)/ParameterDesc.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/test_DSPCallbacks: $(BUILD_DIR)/test_DSPCallbacks.o $(BUILD_DIR)/DSPCallbacks.o $(BUILD_DIR)/ParameterDesc.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/ParameterGetCallbacks.o: ../src/InterfaceAdapter/ParameterGetCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/DSPCallbacks.o: ../src/DSPCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/ParameterDesc.o: ../src/ParameterDesc.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_ParameterGetCallbacks.o: test_ParameterGetCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_DSPCallbacks.o: test_DSPCallbacks.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
