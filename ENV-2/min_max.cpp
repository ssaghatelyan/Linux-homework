#include <iostream>
#include <string>

int main(int n, char* arg[]) {
    if (n != 4) {
        std::cout << "Usage: ./program a b c\n";
        return 1;
    }

    int a, b, c;
    try {
        a = std::stoi(arg[1]);
        b = std::stoi(arg[2]);
        c = std::stoi(arg[3]);
    } catch (const std::exception&) {
        std::cout << "Error\n";
        return 1;
    }

    int min = a, max = a;
    if (b < min) min = b;
    if (c < min) min = c;
    if (b > max) max = b;
    if (c > max) max = c;

    std::cout << "min-" << min << ", max-" << max << "\n";
    return 0;
}
