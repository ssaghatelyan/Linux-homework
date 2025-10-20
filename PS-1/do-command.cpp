#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

void do_command(char** argv) {
    auto start = std::chrono::steady_clock::now();

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed!\n";
        return;
    }
    else if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp");
        _exit(1);
    }
    else {
        int status;
        waitpid(pid, &status, 0);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;

        if (WIFEXITED(status)) {
            std::cout << "Command completed with "
                      << WEXITSTATUS(status)
                      << " exit code and took "
                      << duration.count() << " seconds.\n";
        } else {
            std::cout << "Command terminated abnormally.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << "<command>\n";
        return 1;
    }

    argv++;
    do_command(argv);

    return 0;
}
