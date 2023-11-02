#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.txt>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    std::ifstream inputFile(filename);
    char matrix[10][10], transpose[10][10];

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    int linesRead = 0;

    while (std::getline(inputFile, line)) {
        if (line.size() != 10) {
            std::cerr << "Linedoes not have 10 characters." << std::endl;
            return EXIT_FAILURE;
        }
        for (int j = 0; j < 10; j++) {
            matrix[linesRead][j] = line[j];
        }
        linesRead++;
    }

    if (linesRead != 10) {
        std::cerr << "File does not contain 10 lines." << std::endl;
        return EXIT_FAILURE;
    }

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            transpose[col][row] = matrix[row][col];
        }
    }

    for (int row = 0; row < 10; row++) {
        int left = 0;
        int right = 9;

        while (left < right) {
            std::swap(transpose[row][left], transpose[row][right]);
            left++;
            right--;
        }
    }

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            std::cout << transpose[row][col];
        }
        std::cout << std::endl;
    }

    return 0;
}
