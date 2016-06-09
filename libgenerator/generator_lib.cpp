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
#include "generator.h"

#define BLOCK_SIZE 2048

extern "C" {
void generate(const char* catalog_path, int num_files) {
	std::string file_name;

	// Create a folder
	// Check if it exists first
	struct stat buf;
	int result = stat(catalog_path, &buf);
	printf("result=%i\n", result);
	if(result == -1 && errno == ENOENT) {
		printf("errno is ENOENT\n");
		result = mkdir(catalog_path, 0755);
	}

	int fd_random = open("/dev/urandom", O_RDONLY);
	char buffer[BLOCK_SIZE];

	for(int i=0; i<num_files; i++) {
		// 1) Generate an unique file name
		// 2) Create a file
		// 3) Put something random to a file
		// 4) Close a file
		file_name = std::string(catalog_path) + "/file" + std::to_string(i) + ".txt";
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
}
}
