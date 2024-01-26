CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCES = OF.c functions.c GA.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = GA
LIBRARIES = -lm

all: $(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LIBRARIES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
