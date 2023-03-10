#include <string>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    int grouping = (argc > 1) ? std::stoi(std::string(argv[1])) : 2;
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

    std::cout << "\n";

    for (int i = 0; i < files.size(); i++) {
        std::string prefix = "";
        std::string extension = std::string(files[i].extension());
        std::transform(extension.begin(), extension.end(), extension.begin(),
                        [](unsigned char c){ return std::tolower(c); });
        std::string filename = std::string(files[i].filename());

        if (!extension.compare(".md"))   prefix = "";

        if (!extension.compare(".c")  ||
            !extension.compare(".h"))     prefix = "\033[36m\033[0m";
        if (!extension.compare(".cpp")||
            !extension.compare(".hpp"))   prefix = "\033[36m\033[0m";
        if (!extension.compare(".py"))    prefix = "\033[33m\033[0m";
        if (!extension.compare(".java"))  prefix = "\033[38;5;202m\033[0m";
        if (!extension.compare(".js"))    prefix = "\033[33m\033[0m";
        if (!extension.compare(".ts"))    prefix = "\033[36m\033[0m";
        if (!extension.compare(".json"))  prefix = "\033[33m\033[0m";
        if (!extension.compare(".html"))  prefix = "\033[38;5;202m\033[0m";
        if (!extension.compare(".css"))   prefix = "\033[36m\033[0m";
        if (!extension.compare(".sass")||
            !extension.compare(".scss"))  prefix = "\033[38;5;204m\033[0m";
        if (!extension.compare(".exe") ||
            !extension.compare(".asm") ||
            !extension.compare(".s"))     prefix = "";
        if (!extension.compare(".cs"))    prefix = "\033[35m\033[0m";
        if (!extension.compare(".sql"))   prefix = "\033[36m\033[0m";
        if (!extension.compare(".php"))   prefix = "\033[35m\033[0m";
        if (!extension.compare(".go"))    prefix = "\033[36m\033[0m";
        if (!extension.compare(".rs"))    prefix = "\033[38;5;202m\033[0m";
        if (!extension.compare(".rb"))    prefix = "\033[31m\033[0m";
        if (!extension.compare(".swift")) prefix = "\033[38;5;202m\033[0m";
        if (!extension.compare(".pl"))    prefix = "\033[34m\033[0m";
        if (!extension.compare(".kts") ||
            !extension.compare(".kt"))    prefix = "\033[35m\033[0m";


        if (!extension.compare(".jsx")||
            !extension.compare(".tsx"))  prefix = "\033[36m\033[0m";

        if (!filename.compare(".gitignore")) prefix = "\033[38;5;202m\033[0m";
        if (!filename.compare("Makefile"))   prefix = "";
        if (!filename.compare("LICENSE"))    prefix = "\033[33m\033[0m";

        file_count++;
        std::cout << prefix << " " << filename << "\033[0m " << std::string(longest_file_string_length-filename.size(), ' ');

        if (file_count%grouping == 0) { std::cout << "\n"; };
    }
}
