#include <string>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <unordered_map>

namespace fs = std::filesystem;

std::unordered_map<std::string, std::string> extensions = {
	{".md", "\033[36m\033[0m"},

	{".c", "\033[36m\033[0m"},
	{".h", "\033[36m\033[0m"},
	{".cpp", "\033[36m\033[0m"},
	{".hpp", "\033[36m\033[0m"},

    {".js" , "\033[33m\033[0m"},
    {".ts", "\033[36m\033[0m"},
    {".json", "\033[33m\033[0m"},
    {".html", "\033[38;5;202m\033[0m"},
    {".css", "\033[36m\033[0m"},
    {".sass", "\033[38;5;204m\033[0m"},
    {".scss", "\033[38;5;204m\033[0m"},
	{".jsx", "\033[36m\033[0m"},
	{".tsx", "\033[36m\033[0m"},

    {".exe", ""},
    {".asm", ""},
    {".s"  ,""},
	{".so", ""},

	{".cs", "\033[35m\033[0m"},
	{".java" , "\033[38;5;202m\033[0m"},
	{".py", "\033[33m\033[0m"},

	{".sql", "\033[36m\033[0m"},

	{".php","\033[35m\033[0m"},
	{".go", "\033[36m\033[0m"},
	{".rs", "\033[38;5;202m\033[0m"},
	{".rb", "\033[31m\033[0m"},
	{".swift", "\033[38;5;202m\033[0m"},
	{".pl", "\033[34m\033[0m"},
	{".kts", "\033[35m\033[0m"},
	{".kt", "\033[35m\033[0m"},

	{".sh", ""},
    {".bat", "\033[36m\033[0m"},

    {".dart", "\033[36m\033[0m"},
    {".ex", "\033[35m\033[0m"},
    {".exs", "\033[35m\033[0m"},
    {".erl", "\033[31m\033[0m"},
    {".hrl", "\033[31m\033[0m"},

    {".vim", "\033[32m\033[0m"},
    {".lua", "\033[36m\033[0m"},

    {".jl", ""},

    {".fs", "\033[36m\033[0m"},
    {".fsi", "\033[36m\033[0m"},
    {".fsx", "\033[36m\033[0m"},
    {".fsscript","\033[36m\033[0m"},

    {".coffee","\033[36m\033[0m"},
    {".litcoffee","\033[36m\033[0m"},

    {".scpt" , ""},
    {".scptd", ""},
};

std::unordered_map<std::string, std::string> filenames = {
	{".gitignore",	"\033[38;5;202m\033[0m"},
	{".gitconfig",	"\033[38;5;202m\033[0m"},
	{"Makefile",	""},
	{"LICENSE",		"\033[33m\033[0m"},
};

int main(int argc, char* argv[]) {
    int grouping = 2;
    if (argc > 1) {
        if (!strcmp(argv[1], "--color=auto")) {
            // most likely using ls instead of pls
            try {
                grouping = (argc > 2) ? std::stoi(std::string(argv[2])) : 2;
            } catch (std::invalid_argument) {
                std::cout << "\033[31merror:\033[0m Invalid argument for grouping: Please supply an integer." << std::endl;
                return 1;
            }
        } else {
            try {
                grouping = (argc > 1) ? std::stoi(std::string(argv[1])) : 2;
            } catch (std::invalid_argument) {
                std::cout << "\033[31merror:\033[0m Invalid argument for grouping: Please supply an integer." << std::endl;
                return 1;
            }
        }
    }
    int directory_count = 0;
    int file_count = 0;
    int longest_directory_string_length = 0;
    int longest_file_string_length = 0;
    std::string path = ".";
    std::vector<std::string> directories;
    std::vector<fs::path> files;
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            std::string dir_name = std::string(entry.path().filename());
            directories.push_back(dir_name);

            if (dir_name.size() > longest_directory_string_length) {
                longest_directory_string_length = dir_name.size();
            }
        } else {
            std::string file_name = std::string(entry.path().filename());
            files.push_back(entry.path());

            if (file_name.size() > longest_file_string_length) {
                longest_file_string_length = file_name.size();
            }
        }
    }

    for (int i = 0; i < directories.size(); i++) {
        directory_count++;
        std::cout << "\033[36m " << directories[i] << "\033[0m " << std::string(longest_directory_string_length-directories[i].size(), ' ');

        if (directory_count%grouping == 0) { std::cout << "\n"; };
    }

    if (directories.size()%grouping != 0) std::cout << "\n";

    for (int i = 0; i < files.size(); i++) {
        std::string prefix = "";
        std::string extension = std::string(files[i].extension());
        std::transform(extension.begin(), extension.end(), extension.begin(),
                        [](unsigned char c){ return std::tolower(c); });
        std::string filename = std::string(files[i].filename());

		// Prioritize the extension over the filename
		if (auto e = extensions.find(extension); e != extensions.end()) {
			prefix = e->second;
		}
		else {
			// Filenames
			if (!filename.compare(".gitignore")||
				!filename.compare(".gitconfig")) prefix = "\033[38;5;202m\033[0m";
			if (!filename.compare("Makefile"))   prefix = "";
			if (!filename.compare("LICENSE"))    prefix = "\033[33m\033[0m";
		}


        file_count++;
        std::cout << prefix << " " << filename << "\033[0m " << std::string(longest_file_string_length-filename.size(), ' ');

        if (file_count%grouping == 0) { std::cout << "\n"; };
    }

    if (files.size()%grouping != 0) std::cout << "\n";
}
