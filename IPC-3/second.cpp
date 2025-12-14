#include <iostream>
#include <unistd.h>
#include "shared_array.h"

int main()
{
    shared_array arr("numbers", 4);

    while (true) {
        arr.lock();

        std::cout << "SECOND reads: ";
        for (int i = 0; i < 4; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;

        arr.unlock();

        sleep(1);
    }
}

