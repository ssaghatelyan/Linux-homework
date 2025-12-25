#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void* receive(void* arg) {
	int sock = *(int*)arg;
	char buf[1024];

	while (true) {
		int n = recv(sock, buf, 1024, 0);
		if (n <= 0) break;
		std::cout << buf;
	}
	return NULL;
}

int main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7777);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1

	connect(sock, (sockaddr*)&addr, sizeof(addr));

	pthread_t t;
	pthread_create(&t, NULL, receive, &sock);

	std::string msg;
	while (true) {
		std::getline(std::cin, msg);
		msg += "\n";
		send(sock, msg.c_str(), msg.size(), 0);
		if (msg == "/exit\n")
			break;
	}

	close(sock);
}
