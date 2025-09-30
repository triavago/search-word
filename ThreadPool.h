#pragma once

#include <vector>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "ThreadSafeQueue.h"

class ThreadPool {
private:
	std::vector<std::thread> workers_;
	ThreadSafeQueue& task_queue_;
	std::string keyword_;
	void worker_thread();
public:
	ThreadPool(const int num_threads, const std::string& keyword, ThreadSafeQueue& task_queue);
	~ThreadPool();
};