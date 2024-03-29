#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class Thread {
    private:
        std::thread thread;
 
    public:
        Thread()= default;
        void start();
        void join();
        virtual void run() = 0;
        virtual ~Thread() {}
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
};

#endif
