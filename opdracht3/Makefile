CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = schuifpuzzel

all: $(TARGET)

$(TARGET): schuifpuzzel.c
	$(CC) $(CFLAGS) -o $(TARGET) schuifpuzzel.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
