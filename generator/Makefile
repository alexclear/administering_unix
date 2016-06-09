all: generator libgenerator.so.1.0

generator: generator.o libgenerator.so.1.0
	g++ -g generator.o -o generator -L. -lgenerator

generator.o: generator.cpp
	g++ -g -std=c++11 -c generator.cpp

install: generator libgenerator.so.1.0
	install -m 0755 generator /usr/bin/generator
	install -m 0644 libgenerator.so.1.0 /usr/lib/libgenerator.so.1.0
	ln -s /usr/lib/libgenerator.so.1.0 /usr/lib/libgenerator.so.1
	ln -s /usr/lib/libgenerator.so.1 /usr/lib/libgenerator.so

libgenerator.so.1.0: generator_lib.o
	g++ -shared -Wl,-soname,libgenerator.so.1 -o libgenerator.so.1.0 ./generator_lib.o
	ln -s ./libgenerator.so.1.0 ./libgenerator.so.1
	ln -s ./libgenerator.so.1 ./libgenerator.so

generator_lib.o: generator_lib.cpp
	g++ -g -Wall -std=c++11 -fPIC -c generator_lib.cpp

clean:
	rm -rf *.o
	rm -rf generator libgenerator.so.1.0
