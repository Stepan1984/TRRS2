CC     = gcc
CXX    = g++
CFLAGS = -Wall -Wextra -O2
TARGET = matrix7
TEST   = test_matrix

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

$(TEST): test_matrix.cpp
	$(CXX) $(CFLAGS) -o $(TEST) test_matrix.cpp

test: $(TARGET) $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST)
