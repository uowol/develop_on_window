#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::string filename("demo.csv");
    std::vector<std::string> lines;
    std::string line;

    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line)){
        lines.push_back(line);
    }

    for (const auto &i : lines)
        std::cout << i << std::endl;

    input_file.close();
    return EXIT_SUCCESS;
}
