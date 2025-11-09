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

	while ((bytes = read(src, buf, sizeof(buf))) > 0) {
		for (ssize_t i = 0; i < bytes;) {
        		if (buf[i] == 0) {
                	        ssize_t start = i;
                		while (i < bytes && buf[i] == 0){
                   			 i++;
				}
                		lseek(dst, i - start, SEEK_CUR);
                		hole_bytes += i - start;
           		 } else {
          	               ssize_t start = i;
                		while (i < bytes && buf[i] != 0){
                   			 i++;
				}
               		 write(dst, buf + start, i - start);
                	data_bytes += i - start;
            }
        }
    }

	close(src);
	close(dst);

	ssize_t total = data_bytes + hole_bytes;

	std::cout << "Successfuly copied: " << total  << " bytes: \ndata: " << data_bytes << ", hole: " << hole_bytes << "\n";

}
