CXX = g++
CXXFLAGS = -Wall -Iinclude -Wshadow -pedantic -Wextra -DTEST -Ddebug -O3 -std=c++14
SRCDIR = delivery_optimization
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(EXECUTABLE)
