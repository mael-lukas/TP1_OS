#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
	char *path = "/home/administrateur/CLionProjects/TP1_systemes/test.txt";
	int fd = open(path, O_RDWR);
	if (fd == -1){
		perror("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	struct stat file_stat;
	if (fstat(fd, &file_stat) == -1){
		perror("Error getting file stats\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf("File size: %d bytes\n", file_stat.st_size);

	void *file_map = mmap(NULL, file_stat.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	char *map_char = (char *)file_map;
	for(int i = 0; i < (file_stat.st_size-1)/2; i++){
		char temp  = map_char[i];
		map_char[i] = map_char[file_stat.st_size - 2 - i];
		map_char[file_stat.st_size - 2 - i] = temp;
	}
	munmap(file_map,file_stat.st_size);
	close(fd);

	return 0;
}