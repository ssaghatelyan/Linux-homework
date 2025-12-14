#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <string>

class shared_array
{
public:
    shared_array(const std::string& name, size_t sz)
    {
        size = sz;
        std::string shm_name = "/ipc3_" + name + "_" + std::to_string(size);

        int fd = shm_open(shm_name.c_str(), O_CREAT | O_RDWR, 0666);
        ftruncate(fd, size * sizeof(int));

        data = (int*)mmap(nullptr, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        std::string sem_name = shm_name + "_sem";
        sem = sem_open(sem_name.c_str(), O_CREAT, 0666, 1);
    }

    int& operator[](size_t index) { return data[index];}

    void lock() { sem_wait(sem);}

    void unlock() { sem_post(sem);}

private:
    int* data;
    size_t size;
    sem_t* sem;
};

#endif

