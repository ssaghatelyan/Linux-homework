#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		std::cerr << "Usage: ./read-file <file>\n";
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		std::cerr << "ERROR: cannot open file " << argv[1] << "\n";
		return 1;
	}

	char buffer[4096];
	ssize_t n;
	while((n = read(fd, buffer, sizeof(buffer))) > 0){
		std::cout.write(buffer, n);
	}

	if(n < 0){
		std::cerr << "ERROR: read failed\n";
		close(fd);
		return 1;
	}

	close(fd);
	return 0;
}
