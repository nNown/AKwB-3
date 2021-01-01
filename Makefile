CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -g -Og -std=c++2a
LFLAGS = -lstdc++fs

all: main

main: src/main.cpp src/graph.cpp src/fasta.cpp src/fasta_parser.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LFLAGS)