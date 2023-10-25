#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << "<foldername> <filename.txt>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    double sum = 0.0;
    int num = 0;

    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {
        std::string line;

        while (std::getline(inputFile, line)) {
            int i = std::stoi(line);
            sum = sum + i;
            num++;

            if (i > max){
                max = i;
            }
            if (i < min){
                min = i;
            }
        }

        double average = sum / num;

        std::cout << "Minimum Temperature:    " << min << std::endl;
        std::cout << "Maximum Temperature:   " << max << std::endl;
        std::cout << "Max Temp as octal:     " << std::oct << max << std::endl;
        std::cout << "Max Temp as hex:        " << std::hex << max << std::endl;
        std::cout << "Average Temperature: " << std::fixed << std::setprecision(2) << average << std::endl;
        inputFile.close();

    } else {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
