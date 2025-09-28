#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		std::cerr << "Usage: ./simple-copy <source> <destination>\n";
		return 1;
	}

	int src = open(argv[1], O_RDONLY);
	if(src == -1){
		std::cerr << "Cannot open source\n";
		return 1;
	}

	int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if(dest == -1){
		std::cerr << "Cannot open destination\n";
		return 1;
	}

	char buffer[4096];
	ssize_t n;
	while((n = read(src, buffer, sizeof(buffer))) > 0){
		if(write(dest, buffer, n) != n){
			std::cerr << "ERROR: write failed!\n";
			close(src);
			close(dest);
			return 1;
		}
	}
	close(src);
	close(dest);
	return 0;
}
