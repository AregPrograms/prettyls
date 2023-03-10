#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

int main()
{
    int grouping = 2;
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
        std::cout << "\033[34m " << directories[i] << "\033[0m " << std::string(longest_directory_string_length-directories[i].size(), ' ');

        if (directory_count%grouping == 0) { std::cout << "\n"; };
    }

    for (int i = 0; i < files.size(); i++) {
        std::string prefix = "";
        std::string extension = std::string(files[i].extension());
        std::string filename = std::string(files[i].filename());

        if (!extension.compare(".c")  ||
            !extension.compare(".h"))    prefix = "";
        if (!extension.compare(".cpp")||
            !extension.compare(".hpp"))  prefix = "";
        if (!extension.compare(".py"))   prefix = "";
        if (!extension.compare(".java")) prefix = "";
        if (!extension.compare(".js"))   prefix = "";
        if (!extension.compare(".json")) prefix = "";
        if (!extension.compare(".html")) prefix = "";
        if (!extension.compare(".css"))  prefix = "";
        if (!extension.compare(".sass")||
            !extension.compare(".scss")) prefix = "";
        if (!extension.compare(".exe") ||
            !extension.compare(".asm") ||
            !extension.compare(".s"))    prefix = "";

        if (!extension.compare(".jsx")||
            !extension.compare(".tsx"))  prefix = "";

        if (!filename.compare(".gitignore")) prefix = "";

        file_count++;
        std::cout << prefix << " " << filename << "\033[0m " << std::string(longest_file_string_length-filename.size(), ' ');

        if (file_count%grouping == 0) { std::cout << "\n"; };
    }
}
