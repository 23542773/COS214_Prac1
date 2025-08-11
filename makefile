CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g --coverage
LDFLAGS = --coverage

TARGET = app
OBJS = OpemCanvas.o Test.o

all: $(TARGET)

OpemCanvas.o: OpemCanvas.cpp OpenCanvas.h
	$(CXX) $(CXXFLAGS) -c OpemCanvas.cpp

Test.o: Test.cpp OpenCanvas.h
	$(CXX) $(CXXFLAGS) -c Test.cpp

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

# Generate coverage report
coverage: clean all run
	gcov OpemCanvas.cpp TestingMain.cpp

clean:
	rm -f *.o $(TARGET) *.gcda *.gcno *.gcov
