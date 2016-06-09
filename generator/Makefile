all: generator

generator: generator.o
	g++ -g generator.o -o generator -L. -lgenerator

generator.o: generator.cpp
	g++ -g -std=c++11 -c generator.cpp

install: generator
	install -m 0755 generator /usr/bin/generator

clean:
	rm -rf *.o
	rm -rf generator
