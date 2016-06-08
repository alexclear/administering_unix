#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
//#include "generator.h"
#include <dlfcn.h>

#define BLOCK_SIZE 2048

int main(int argc, char** argv) {
	int flags, opt;
	std::string catalog_path;
	std::string file_name;
	int num_files = 1000;
	char *error;
	void (*fn)(const char*, int);

	while ((opt = getopt(argc, argv, "c:p:")) != -1) {
		switch (opt) {
			case 'p':
				catalog_path = optarg;
				break;
			case 'c':
				num_files = atoi(optarg);
				break;
			default: /* '?' */
				fprintf(stderr, "Usage: %s -p catalog_path\n",
						argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if(num_files <= 0) {
		fprintf(stderr, "Please set num_files to a positive number\n");
		exit(EXIT_FAILURE);
	}
	printf("path=%s, num_files:%d\n", catalog_path.c_str(), num_files);

	void *lib_handle;

	lib_handle = dlopen("./libgenerator.so", RTLD_LAZY);
	if (!lib_handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	fn = (void (*)(const char*, int))dlsym(lib_handle, "generate");
	if ((error = dlerror()) != NULL) 
	{
	      fprintf(stderr, "%s\n", error);
	      exit(EXIT_FAILURE);
	}
	 
	(*fn)(catalog_path.c_str(), num_files);

	/*
	// Create a folder
	// Check if it exists first
	struct stat buf;
	int result = stat(catalog_path.c_str(), &buf);
	printf("result=%i\n", result);
	if(result == -1 && errno == ENOENT) {
		printf("errno is ENOENT\n");
		result = mkdir(catalog_path.c_str(), 0755);
	}

	int fd_random = open("/dev/urandom", O_RDONLY);
	char buffer[BLOCK_SIZE];

	for(int i=0; i<num_files; i++) {
		// 1) Generate an unique file name
		// 2) Create a file
		// 3) Put something random to a file
		// 4) Close a file
		file_name = catalog_path + "/file" + std::to_string(i) + ".txt";
		printf("file_name=%s\n", file_name.c_str());
		result = stat(file_name.c_str(), &buf);
//		if(result == -1 && errno == ENOENT) {
		int fd = open(file_name.c_str(), O_WRONLY | O_CREAT, 0644);
		if(fd == -1) {
			fprintf(stderr, "Error opening/creating a file, error: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
		int nr_bytes = read(fd_random, buffer, BLOCK_SIZE);
		if(nr_bytes == -1) {
			fprintf(stderr, "Error reading random sequence");
			exit(EXIT_FAILURE);
		}
		if(nr_bytes != BLOCK_SIZE) {
			fprintf(stderr, "Number of bytes read is not %i, it is %i!", BLOCK_SIZE, nr_bytes);
			exit(EXIT_FAILURE);
		}
		result = write(fd, buffer, BLOCK_SIZE);
		if(result == -1) {
			fprintf(stderr, "Error writing to a file");
			exit(EXIT_FAILURE);
		}
		result = close(fd);
		if(result == -1) {
			fprintf(stderr, "Error closing to a file");
			exit(EXIT_FAILURE);
		}
//		}
	}
	close(fd_random);
*/
	exit(EXIT_SUCCESS);
}
