CC=g++
CFLAGS=-c -ggdb -g -Wall
# -Wextra -Wpedantic -Weffc++ -lstdc++
LDFLAGS=
SOURCES= Gene.cpp Population.cpp Main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o core
