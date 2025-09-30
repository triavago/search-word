// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*if (argc != 4) {
		std::cout << "Invalid argurment" << std::endl;
		std::cout << argc << std::endl;
		std::cout << argv[1] << std::endl;
		std::cout << argv[2] << std::endl;
		return 1;
	}*/

	std::string file_path = "D:/learn/code/urprj/file search/text_to_find";
	std::string key_word = "bookshelf";
	const unsigned int thread_num = std::thread::hardware_concurrency();
	std::cout << "thread nums: " << thread_num << std::endl;

	ThreadSafeQueue job_queue;
	ThreadPool pool(thread_num, key_word, job_queue);

	for (auto dir : std::filesystem::recursive_directory_iterator(file_path)) {
		if (!dir.is_regular_file()) {
			continue;
		}
		job_queue.push(dir.path().string());
	}

	job_queue.set_done();

	return 0;
}
