#include "common_Thread.h"

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

bool Thread::joinable() {
    return thread.joinable();
}
