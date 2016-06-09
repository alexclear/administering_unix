all: libgenerator.so.1.0

install: libgenerator.so.1.0
	install -m 0644 libgenerator.so.1.0 /usr/lib/libgenerator.so.1.0
	install -m 0644 generator.h /usr/include/generator.h
	test -L /usr/lib/libgenerator.so.1 && unlink /usr/lib/libgenerator.so.1
	ln -s /usr/lib/libgenerator.so.1.0 /usr/lib/libgenerator.so.1
	test -L /usr/lib/libgenerator.so && unlink /usr/lib/libgenerator.so
	ln -s /usr/lib/libgenerator.so.1 /usr/lib/libgenerator.so

libgenerator.so.1.0: generator_lib.o
	g++ -shared -Wl,-soname,libgenerator.so.1 -o libgenerator.so.1.0 ./generator_lib.o

generator_lib.o: generator_lib.cpp
	g++ -g -Wall -std=c++11 -fPIC -c generator_lib.cpp

clean:
	rm -rf *.o
	rm -rf libgenerator.so.1.0
