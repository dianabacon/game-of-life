# Filename: makefile
# Author: Diana Bacon
# Date: 2015-09-23
# Description: compile CS162 Lab 1 program to compare
#              rolls of a regular and loaded die
#
# Command to build program: make
# Command to execute program: ./life

CC=g++
CFLAGS=-c -g -Wall -pedantic-errors
LDFLAGS=
SOURCES = Seed.cpp Game.cpp  Grid.cpp  main.cpp
HEADERS = Seed.hpp Game.hpp  Grid.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE = life

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f ${OBJECTS} ${EXECUTABLE}
