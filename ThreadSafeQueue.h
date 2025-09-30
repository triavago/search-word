#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadSafeQueue {
private:
    std::queue<std::string> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;
    bool is_done_ = false;
public:
    void push(const std::string& value);
    bool pop(std::string& value);
    void set_done();
};