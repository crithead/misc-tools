CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SOURCES := main.cpp math.cpp
HEADERS := math.hpp
OBJECTS := $(SOURCES:.cpp=.o)

TEST_SOURCES := test_main.cpp test_math.cpp
TEST_OBJECTS := $(TEST_SOURCES:.cpp=.o)

program: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

tester: $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) -o $@ $(filter-out main.o, $^)

test: tester
	./tester

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) program tester

.PHONY: clean test
