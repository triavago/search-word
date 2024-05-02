#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <regex>
#include <sstream>
#include <set>

void search_in_file(const std::string& filename, const std::string& words, std::set<std::string> &fileNameSet) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << '\n';
        return;
    }

    std::string line;
    std::string word;
    word = "\\b" + words + "\\b";
    std::regex wordRegex(word);
    
    while (std::getline(file, line)) {
        std::sregex_iterator iter(line.begin(), line.end(), wordRegex);
        std::sregex_iterator end;
        while (iter != end)
        {
            fileNameSet.insert(filename);
            return;
        }
    }
}

void search_in_directory(const std::string& directory, const std::vector<std::string> wordsContainer) {
    std::set<std::string> fileNameSet;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            for (auto& word : wordsContainer)
            {
                search_in_file(entry.path().string(), word, fileNameSet);
            }
        }
    }
    for (auto& i : fileNameSet)
    {
        std::cout << i << " " << std::endl;
    }
}

int main(int argc, char* argv[]) {
   /* if (argc != 3) {
        std::cerr << "Usage: ./program <directory> <words>\n";
        return 1;
    }*/

    /*std::string directory = argv[2];
    std::string words = argv[1];*/
    std::string directory = "D:\\private\\search";
    std:: string words = "book cat";
    std::vector<std::string> wordsContainer;
    std::istringstream iss(words);
    std::string word;
    while (iss >> word)
    {
        wordsContainer.push_back(word);
    }

    search_in_directory(directory, wordsContainer);

    return 0;
}
