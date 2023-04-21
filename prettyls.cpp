#include <string>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdlib.h>

// std::filesystem is C++17
// Stating this standard is explicitly required by Clang and Clang-based LSPs
namespace fs = std::filesystem;

std::unordered_map<std::string, std::string> extensions = {
	{".md", "\033[36m\033[0m"},
    {".pdf", "\033[31m\033[0m"},

    {".jpg", ""},
    {".png", ""},
    {".tiff", ""},
    {".bmp", ""},
    {".heic", ""},

    {".mp4", ""},
    {".mov", ""},
    {".avi", ""},
    {".mkv", ""},
    {".webm", ""},
    {".flv", ""},
    {".gif", ""},

	{".c", "\033[36m\033[0m"},
	{".h", "\033[36m\033[0m"},
	{".cpp", "\033[36m\033[0m"},
	{".hpp", "\033[36m\033[0m"},

    {".d", "\033[31m\033[0m"},

    {".js" , "\033[33m\033[0m"},
    {".ts", "\033[36m\033[0m"},
    {".json", "\033[33m\033[0m"},
    {".json5", "\033[33m\033[0m"},
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

    {".hs", "\033[35m\033[0m"},
    {".lhs", "\033[35m\033[0m"},

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

    {".ttf", "\033[31m\033[0m"},
    {".otf", "\033[31m\033[0m"},
    {".woff", "\033[31m\033[0m"},
    {".woff2", "\033[31m\033[0m"},
    {".fnt", "\033[31m\033[0m"},
};

std::unordered_map<std::string, std::string> filenames = {
	{".gitignore",	"\033[38;5;202m\033[0m"},
	{".gitconfig",	"\033[38;5;202m\033[0m"},
	{"Makefile",	""},
	{"LICENSE",		"\033[33m\033[0m"},
    {"package.json", "\033[32m\033[0m"},
    {"package-lock.json", "\033[32m\033[0m"},

	{".csproj", "\033[35m\033[0m"},
};

std::unordered_map<std::string, std::string> folders = {
    {"Downloads", ""},
    {"Documents", ""},
    {"Desktop", ""},
    {"Pictures", ""},
    {"Videos", ""},

    {"css", ""},
    {"html", ""},
    {"js", ""},
    {"javascript", ""},
    
    {"database", ""},
    {"databases", ""},
    {"db", ""},
    {"schemas", ""},

    {"test", "ﭧ"},
    {"tests", "ﭧ"},

    {"node_modules", ""},
     
    {"react", ""},
};

std::vector<std::string> split(std::string str, char separator) {
    std::vector<std::string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= (int)str.size(); i++) {
        
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == (int)str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return strings;
}

int main(int argc, char* argv[]) {
    int grouping = 2;
    std::string path = ".";
    if (argc > 1) {
        if (!strcmp(argv[1], "--color=auto")) {
            // most likely using ls instead of pls
            if (argc > 2) path = std::string(argv[2]);
        } else {
            path = std::string(argv[1]);
        }
    }
    int directory_count = 0;
    int file_count = 0;
    long unsigned int longest_directory_string_length = 0;
    long unsigned int longest_file_string_length = 0;
    std::vector<std::string> directories;
    std::vector<fs::path> files;

    std::string line;
    std::ifstream config_file(std::string(getenv("HOME")) + "/.config/.prettyls");

    while (getline(config_file, line)) {
        std::vector<std::string> s = split(line, ':');

        if (!s[0].compare("grouping")) {
            if (s.size() > 1)
                grouping = atoi(s[1].c_str());
            else
                std::cout << "\033[31merror:\033[0m Please supply a valid integer for grouping." << std::endl;
        }
    }
    
    try {
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

        for (long unsigned int i = 0; i < directories.size(); i++) {
            std::string folder_name = directories[i];

            std::string icon = "";

            std::transform(folder_name.begin(), folder_name.end(), folder_name.begin(),
                            [](unsigned char c){ return std::tolower(c); });

            if (auto f = folders.find(directories[i]); f != folders.end()) {
                icon = f->second;
            }

            directory_count++;
            std::cout << ((directories[i][0] == '.') ? "\033[38;5;8m" : "\033[36m") << icon << " " << directories[i] << "\033[0m " << std::string(longest_directory_string_length-directories[i].size(), ' ');

            if (directory_count%grouping == 0) std::cout << "\n";
        }

        if (directories.size()%grouping != 0) std::cout << "\n";

        for (long unsigned int i = 0; i < files.size(); i++) {
            std::string prefix = "";
            std::string extension = std::string(files[i].extension());
            std::transform(extension.begin(), extension.end(), extension.begin(),
                            [](unsigned char c){ return std::tolower(c); });
            std::string filename = std::string(files[i].filename());

            // Prioritize the extension over the filename
            if (auto e = extensions.find(extension); e != extensions.end()) {
                prefix = e->second;
            }
            // Filenames
            if (auto f = filenames.find(filename); f != filenames.end()) {
                prefix = f->second;
            }

            file_count++;
            std::cout << prefix << " " << filename << "\033[0m " << std::string(longest_file_string_length-filename.size(), ' ');

            if (file_count%grouping == 0) std::cout << "\n";
        }

        if (files.size()%grouping != 0) std::cout << "\n";
    } catch (std::filesystem::__cxx11::filesystem_error const&) {
        std::cout << "\033[31merror:\033[0m Error occured while trying to open path \"" << path << "\"" << std::endl;
    }
}
