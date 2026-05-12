CC     = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = matrix7
TEST   = test_matrix

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

$(TEST): test_matrix.c
	$(CC) $(CFLAGS) -o $(TEST) test_matrix.c

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST) main.o
