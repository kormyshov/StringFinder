TARGET=$(shell basename `pwd`)
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:%.c=%.o)

CC=gcc

CPPFLAGS+=-O2 -L/usr/include
LDFLAGS+=-O2 -L/usr/include

all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LOADLIBES) $(LDLIBS)

clean:
		$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
