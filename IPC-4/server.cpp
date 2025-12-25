#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <algorithm>

std::vector<int> clients;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* clientHandler(void* arg) {
	int sock = *(int*)arg;
	char buf[1024];

	while (true) {
		int n = recv(sock, buf, 1024, 0);
		if (n <= 0) break;
		std::string msg(buf, n);
		if (msg == "/exit\n" || msg == "/exit") {
			break;
		}

		if (msg == "/list\n" || msg == "/list") {
			pthread_mutex_lock(&mutex);
			std::string ans = "Clients count: ";
			ans += std::to_string(clients.size()) + "\n";
			pthread_mutex_unlock(&mutex);
			send(sock, ans.c_str(), ans.size(), 0);
			continue;
		}

		pthread_mutex_lock(&mutex);
		for (int c : clients) {
			send(c, buf, n, 0);
		}
		pthread_mutex_unlock(&mutex);
	}

       	pthread_mutex_lock(&mutex);
	clients.erase(std::remove(clients.begin(), clients.end(), sock),clients.end());
	pthread_mutex_unlock(&mutex);

	close(sock);
	return NULL;
}

int main() {
	int server = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7777);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(server, (sockaddr*)&addr, sizeof(addr));
	listen(server, 5);

	std::cout << "Server started\n";

	while (true) {
		int client = accept(server, NULL, NULL);

		pthread_mutex_lock(&mutex);
		clients.push_back(client);
		pthread_mutex_unlock(&mutex);

		pthread_t t;
		pthread_create(&t, NULL, clientHandler, &client);
		pthread_detach(t);
	}
}
