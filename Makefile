CC=g++
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=$(shell ls *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARIES=-lpthread
TARGET=processor

all: .depend $(TARGET)
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET) $(LIBRARIES)

.depend: $(SOURCES)
	rm -f $@
	$(CC) -MM $(SOURCES) >> $@

include .depend

clean:
	rm .depend $(TARGET) *.o
