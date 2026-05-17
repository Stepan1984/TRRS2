CC     = g++
CFLAGS = -Wall -Wextra -O2
TARGET = matrix7
TEST   = test_matrix

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp \
		-lprometheus-cpp-pull \
		-lprometheus-cpp-core \
		-lprometheus-cpp-push \
		-lz -lpthread

$(TEST): test_matrix.cpp
	$(CC) $(CFLAGS) -o $(TEST) test_matrix.cpp

test: $(TARGET) $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST)
