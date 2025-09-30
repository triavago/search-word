#include "ThreadPool.h"

static	std::mutex mutex_cout;
constexpr int BUFFER_SIZE = 8192;

bool search_file_for_key_word(const std::string& file_path, const std::string& key_word) {
	std::vector<char> chunk(BUFFER_SIZE);
	std::ifstream file(file_path);
	std::regex key_word_regex(key_word);
	if (file.is_open()) {
		//while (std::getline(file, line)) {
		std::string cache;
		while (!file.eof()) {
			file.read(chunk.data(), BUFFER_SIZE);
			std::string data = std::string(chunk.begin(), chunk.end());
			data = cache + data;
			if (std::regex_search(data, key_word_regex)) {
				{
					std::lock_guard<std::mutex> lock(mutex_cout);
					std::cout << "Found at:" << file_path + "\n" << std::endl;
				}
				return true;
			}
			cache = std::string(chunk.end() - key_word.size(), chunk.end());
		}
	}
	file.close();
	return false;
}

ThreadPool::ThreadPool(const int num_threads, const std::string& keyword, ThreadSafeQueue& task_queue) : keyword_(keyword), task_queue_(task_queue) {
	for (int i = 0; i < num_threads; i++) {
		workers_.emplace_back(&ThreadPool::worker_thread, this);
	}
}

void ThreadPool::worker_thread() {
	while (true) {
		std::string job;
		bool has_value = task_queue_.pop(job);
		if (!has_value)
			break;
		search_file_for_key_word(job, keyword_);
	}
}

ThreadPool::~ThreadPool() {
	for (auto& worker : workers_) {
		if (worker.joinable())
			worker.join();
	}
}