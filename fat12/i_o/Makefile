CC=gcc
CCFLAGS=-Wall

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

EXECUTABLE=fat # change executable name as needed

$(EXECUTABLE): $(OBJECTS)
	make clean # added for convenience with our preferred IDE
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@
	mkdir build
	mv $(OBJECTS) $(EXECUTABLE) build

$(SOURCES):
	$(CC) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf build
