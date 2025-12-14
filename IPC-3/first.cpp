#include <iostream>
#include <unistd.h>
#include "shared_array.h"

int main() {
    shared_array arr("numbers", 4);
    int value = 0;

    while (true)
    {
        arr.lock();

        for (int i = 0; i < 4; i++)
            arr[i] = value + i;

        std::cout << "FIRST writes: ";
        for (int i = 0; i < 4; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;

        arr.unlock();
        value++;

        sleep(1);
    }
}
