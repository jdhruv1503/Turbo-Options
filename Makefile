CXX = g++
CXXFLAGS = -std=c++11 -O2 -I./src

TARGET = bin/pricer
TEST_TARGET = bin/test_option
SRCS = src/main.cpp src/option.cpp src/pricing_model.cpp src/market_data.cpp src/math_utils.cpp
TEST_SRCS = tests/test_option.cpp src/option.cpp src/pricing_model.cpp src/market_data.cpp src/math_utils.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS) | bin
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS) | bin
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

bin:
	mkdir -p bin

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)
	rm -rf bin