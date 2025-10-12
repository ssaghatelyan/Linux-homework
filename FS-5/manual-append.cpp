#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "Usage: " << argv[0] << "<file>\n";
		exit(1);
	}

	const char* file = argv[1];

	int fd1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd1 == -1) {
		std::cerr << "Error opening file\n";
		exit(1);
	}

	int fd2 = dup(fd1);
	if(fd2 == -1) {
		std::cerr << "Error duplicating descriptor\n";
		close(fd1);
		exit(1);
	}

	const char* line1 = "first line\n";
	if(write(fd1, line1, 11) == -1) {
		std::cerr << "Error writing first line\n";
		close(fd1);
		close(fd2);
		exit(1);
	}

	const char* line2 = "second line\n";
        if(write(fd2, line2, 12) == -1) {
                std::cerr << "Error writing second line\n";
                close(fd1);
		close(fd2);
                exit(1);
        }

	close(fd1);
	close(fd2);

}
