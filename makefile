CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g --coverage
LDFLAGS = --coverage

TARGET = app
OBJS = OpemCanvas.o TestingMain.o

all: $(TARGET)

OpemCanvas.o: OpemCanvas.cpp OpenCanvas.h
	$(CXX) $(CXXFLAGS) -c OpemCanvas.cpp

TestingMain.o: TestingMain.cpp OpenCanvas.h
	$(CXX) $(CXXFLAGS) -c TestingMain.cpp

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

# Generate coverage report
# Generate text coverage report using gcov
coverage: clean $(TARGET) run
	gcov -b OpemCanvas.cpp TestingMain.cpp > coverage.txt
	

clean:
	rm -rf *.o $(TARGET) *.gcda *.gcno *.gcov coverage.info coverage_report