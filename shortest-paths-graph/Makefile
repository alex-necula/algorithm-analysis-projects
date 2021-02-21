CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

build: build_dijkstra

run:
	./tester

build_dijkstra: algo1.o tester.o
	$(CC) $(CFLAGS) $^ -o tester

build_floyd: algo2.o tester.o
	$(CC) $(CFLAGS) $^ -o tester

build_bellman: algo3.o tester.o
	$(CC) $(CFLAGS) $^ -o tester

build_johnson: algo4.o tester.o
	$(CC) $(CFLAGS) $^ -o tester

generator: generator.o
	$(CC) $(CFLAGS) $^ -o generator

algo1.o: algo1.cpp
	$(CC) $^ -c $(CFLAGS)

algo2.o: algo2.cpp
	$(CC) $^ -c $(CFLAGS)

algo3.o: algo3.cpp
	$(CC) $^ -c $(CFLAGS)

algo4.o: algo4.cpp
	$(CC) $^ -c $(CFLAGS)

tester.o: tester.cpp
	$(CC) $^ -c $(CFLAGS)

generator.o: generator.cpp
	$(CC) $^ -c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o tester generator