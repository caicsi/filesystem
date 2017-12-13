CC=gcc
CCFLAGS=-Wall

SOURCES=$(wildcard *.c ./commands/*.c)
OBJECTS=$(SOURCES:.c=.o)

EXECUTABLE=fat12 # change executable name as needed

$(EXECUTABLE): $(OBJECTS)
	make clean # line added for convenience while testing
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@
	mkdir build
	mv $(OBJECTS) $(EXECUTABLE) build

$(SOURCES):
	$(CC) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf build
