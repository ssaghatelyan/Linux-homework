#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#define buf_size 4096

int main(int argc, char* argv[]) {
	if(argc != 3) {
		std::cerr << "Usage: " << argv[0] << "<source file> <destination file>\n";
		exit(1);
	}

	int src = open(argv[1], O_RDONLY);
	if(src == -1) {
		std::cerr << "Error opening source file\n";
		exit(1);
	}

	int dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(dst == -1) {
		std::cout << "Error opening destination file\n";
		close(src);
		exit(1);
	}
	
	char buf[buf_size];
	ssize_t bytes;
	ssize_t data_bytes = 0;
	ssize_t hole_bytes = 0;

	while ((bytes = read(src, buf, sizeof(buf))) > 0){
		ssize_t i = 0;
		while(i < bytes){
			if(buf[i] != 0) {
				ssize_t  j = i;
				while (j < bytes && buf[j] != 0) {
					j++;
				}
				ssize_t written = write(dst, buf + i, j - i);
            			if (written != j - i) { 
					std::cerr << "Error writing\n";
					exit(1);
				}
				data_bytes += j - i;
				i = j;
			}
			else{
				ssize_t j = i;
				while (j < bytes && buf[j] == 0) {
                                        j++;
                                }
                                if (lseek(dst, j - i, SEEK_CUR) == -1) {
					std::cerr << "Error with lseek\n";
				       	exit(1);
			       	}
				hole_bytes += j - i;
                                i = j;
			}
		}
	}
	if(bytes == -1) {
		std::cerr << "Error reading source file\n";
		exit(1);
	}

	close(src);
	close(dst);

	if(bytes == -1) {
		std::cerr << "Error reading file\n";
		exit(1);
	}

	std::cout << "Successfuly copied: " << (data_bytes + hole_bytes) << " bytes: \ndata: " << data_bytes << ", hole: " << hole_bytes << "\n";

}
