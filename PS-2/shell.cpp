#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdlib>

int main() {
    std::string original_path;
    if (std::getenv("PATH") != nullptr) {
        original_path = std::getenv("PATH");
    } else {
        original_path = "";
    }
    
    while(true) {
        std::cout << "shell$ ";
        std::string input;
        std::getline(std::cin, input);
        
        if(input == "exit") break;
        if(input.empty()) continue;
        
        std::vector<std::vector<std::string>> commands;
        std::vector<std::string> operators;
        std::vector<std::string> current_command;
        std::stringstream ss(input);
        std::string token;
        
        while(ss >> token) {
            if(token == ";" || token == "&&" || token == "||") {
                if(!current_command.empty()) {
                    commands.push_back(current_command);
                    operators.push_back(token);
                    current_command.clear();
                }
            } else {
                current_command.push_back(token);
            }
        }
        if(!current_command.empty()) commands.push_back(current_command);
        
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd))) {
            setenv("PATH", (std::string(cwd) + ":" + original_path).c_str(), 1);
        }
        
        int last_status = 0;
        bool should_execute = true;
        
        for(size_t i = 0; i < commands.size(); i++) {
            if(!should_execute || commands[i].empty()) continue;
            
            bool silent = false;
            std::string output_file;
            bool append = false;
            std::vector<std::string> args;
            
            for(size_t j = 0; j < commands[i].size(); j++) {
                if(j == 0 && commands[i][j] == "silent") {
                    silent = true;
                } else if(commands[i][j] == ">" && j+1 < commands[i].size()) {
                    output_file = commands[i][++j];
                } else if(commands[i][j] == ">>" && j+1 < commands[i].size()) {
                    output_file = commands[i][++j];
                    append = true;
                } else {
                    args.push_back(commands[i][j]);
                }
            }
            
            if(args.empty()) continue;
            
            pid_t pid = fork();
            if(pid == 0) {
                if(silent) {
                    std::string filename = std::to_string(getpid()) + ".log";
                    int fd = open(filename.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    dup2(fd, STDERR_FILENO);
                    close(fd);
                } else if(!output_file.empty()) {
                    int flags = O_WRONLY|O_CREAT | (append ? O_APPEND : O_TRUNC);
                    int fd = open(output_file.c_str(), flags, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                
                std::vector<char*> cargs;
                for(auto& arg : args) cargs.push_back(&arg[0]);
                cargs.push_back(nullptr);
                
                execvp(cargs[0], cargs.data());
                exit(127);
            }
            
            int status;
            waitpid(pid, &status, 0);
            last_status = WEXITSTATUS(status);
            bool success = (last_status == 0);
            
            if(i < operators.size()) {
                if(operators[i] == "&&") should_execute = success;
                else if(operators[i] == "||") should_execute = !success;
                else should_execute = true; // ;
            }
        }
        
        setenv("PATH", original_path.c_str(), 1);
    }
    return 0;
}
