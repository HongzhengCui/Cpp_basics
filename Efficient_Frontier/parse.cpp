#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib> 
#include "parse.hpp"

std::vector<std::string> split_line(const std::string& line) {
    std::vector<std::string> fields;
    std::istringstream ss(line);
    std::string field;
    // Split each line with comma
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

void read_universe(const std::string& filename, std::vector<std::string>& asset_name, std::vector<double>& average_rate_of_return, std::vector<double>& standard_deviation){
    std::ifstream in(filename);
    // The file can be operated
    if (!in.is_open()) {
        std::cerr << "Unable to open '" + filename + "'." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;

    while (getline(in, line)) {
        std::vector<std::string> fields = split_line(line);
        // The universe.csv should contain three attributes: Asset name, Average of return and Standard deviation
        if (fields.size() != 3){
            std::cerr << "The content dimension of the '" + filename + "' should be 3." << std::endl;
            exit(EXIT_FAILURE);
        }

        asset_name.push_back(fields[0]);
        // Convert the strings to double values
        try {
            average_rate_of_return.push_back(stod(fields[1]));
            standard_deviation.push_back(stod(fields[2]));
        } 
        catch (...) {
            std::cerr << "The data value can not be converted to double correctly." << std::endl;
            exit(EXIT_FAILURE);
        }

        if (stod(fields[2]) > 1) {
            std::cerr <<"The standard deviation value can not be greater than 1." << std::endl;
            exit(EXIT_FAILURE);
        }
        
    }
    in.close();
}

void read_correlation(const std::string& filename, std::vector<std::vector<double>>& correlation_vectors){
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Unable to open '" + filename + "'." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;

    while (getline(in, line)) {
        std::vector<std::string> fields = split_line(line);

        std::vector<double> values;

        for (const auto& field: fields){
            try {
                values.push_back(stod(field));
            } 
            catch (...) {
                std::cerr <<"The data value can not be converted to double correctly." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        correlation_vectors.push_back(values);
    }
    // The correlation vectors should be 2D square matrix
    if (correlation_vectors.size() != correlation_vectors[0].size()){
        std::cerr << "The correlation matrix should be a square matrix." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Check the correlation data file
    for (size_t i = 0; i < correlation_vectors.size(); ++i){
        for (size_t j = 0; j < correlation_vectors[i].size(); ++j){
            if (i == j) {
                if (correlation_vectors[i][j] != 1) {
                    std::cerr << "The values at the diagonal line of correlation matrix should be 1." << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                if (correlation_vectors[i][j] != correlation_vectors[j][i]) {
                    std::cerr << "The data in correlation matrix in the file should be symmetrical." << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    in.close();
}