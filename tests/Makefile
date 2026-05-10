CXX = g++
CXXFLAGS = -std=c++20 -I../src -I./include
BUILD_DIR = build

OBJS_PARAM = $(BUILD_DIR)/ParameterGetCallbacks.o $(BUILD_DIR)/test_ParameterGetCallbacks.o
OBJS_DSP = $(BUILD_DIR)/DSPCallbacks.o $(BUILD_DIR)/ParameterDesc.o $(BUILD_DIR)/TapeStopEngine.o $(BUILD_DIR)/DelayLine.o $(BUILD_DIR)/OnePoleLowpass.o $(BUILD_DIR)/test_DSPCallbacks.o

all: $(BUILD_DIR)/test_param $(BUILD_DIR)/test_dsp

$(BUILD_DIR)/test_param: $(OBJS_PARAM)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/test_dsp: $(OBJS_DSP)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: ../src/InterfaceAdapter/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: ../src/Framework/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: ../src/UseCase/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: ../src/Domain/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
