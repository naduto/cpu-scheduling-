CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = lab7
SRC = lab7.cpp
all: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET) *.o