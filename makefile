CC=gcc
CFLAGS=-c -Wall -g -std=c11 -D_LOG_ALERT -D_LOG_VERBOSE
LDFLAGS=-lpthread
SOURCES=$(shell ls *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=dns

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.h.c:
	@touch $@

rebuild: clean all

clean:
	rm *.o
