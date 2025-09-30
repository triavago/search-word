#include "ThreadSafeQueue.h"

void ThreadSafeQueue::push(const std::string& value) {
	std::lock_guard<std::mutex> lock(mutex_);
	queue_.push(value);
	cond_var_.notify_one();
}

bool ThreadSafeQueue::pop(std::string& value) {
	std::unique_lock<std::mutex> lock(mutex_);
	cond_var_.wait(lock, [this] {
		return !queue_.empty() || is_done_;
		});
	if (queue_.empty() && is_done_) {
		return false;
	}
	value = queue_.front();
	queue_.pop();
	return true;
}

void ThreadSafeQueue::set_done() {
	std::lock_guard<std::mutex> lock(mutex_);
	is_done_ = true;
	cond_var_.notify_all();
}