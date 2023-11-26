#include "asset.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>
using namespace std;

int main(int argc, char* argv[]) {

    // Check if the input argument is correct
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " filename.csv" << endl;
        return EXIT_FAILURE;
    }

    string filename = argv[1];
    ifstream file(filename);

    // Check if the file can be operated correctly
    if (!file.is_open()) {
        cerr << "The file failed to open. Please input the correct file." << endl;
        return EXIT_FAILURE;
    }

    string row;
    vector<vector<double>> dataset;
    size_t row_index = 0, column = 0;
    
    while (getline(file, row)) {
        if (row_index > 0) {
            // Gap the first row: Headers
            stringstream s(row);
            string element;

            getline(s, element, ',');  // Gap the first column: Time or Date
            dataset.push_back(vector<double>());  // Initialize 2D vector to store the matrix
            double value = 0;

            for (size_t i = 0; getline(s, element, ','); i++) {
                if (row_index == 1){
                    // Check if the value 'null' appears in the first data record
                    if (element == "null"){
                        cerr << "The first data record should be valid." << endl;
                        return EXIT_FAILURE;
                    } else{
                        value = stod(element);
                    }
                } else{
                    // Replace the 'null' to the previous value in the same column
                    if (element == "null"){
                        value = dataset[row_index - 2][i];
                    } else{
                        value = stod(element);
                    }    
                }
                dataset[row_index - 1].push_back(value);
            }
        }    
        else{
            stringstream s(row);
            string element;
            // Print the header names
            for (size_t i = 0; getline(s, element, ','); i++) {
                column++;
                if (i > 0){
                    cout << element << endl;
                }
            }
        }
        row_index++;
    }

    for (size_t i = 0; i < row_index - 1; i++){
        // Check if the dataset row size is coresponding to the header
        if (dataset[i].size() + 1 != column){
            cerr << "The file dataset size is not corret. Please check the header columns." << endl;
            return EXIT_FAILURE;
        }
    }

    // Integrate all rates into one 2D vector
    vector<vector<double>> total_rates;
    // Calculate the rates of one column and store them in a vector as each total_rates' row
    for (size_t j = 0; j < column - 1; j++) {
        vector<double> rates;
        for (size_t i = 1; i < row_index - 1; i++) {
            double rate = dataset[i][j] / dataset[i-1][j] - 1;
            rates.push_back(rate);
        }
        total_rates.push_back(rates);
    }

    vector<vector<double>> correl_AB = CorrelMatrix(total_rates);

    // Print the result according to the format
    cout << "[";
    for (size_t i = 0; i < correl_AB.size(); i++) {
        if (i > 0){
            cout << " ";
        }
        for (size_t j = 0; j < correl_AB[i].size(); j++) {
            if (i == j){
                correl_AB[i][j] = 1;
            }
            if (correl_AB[i][j] >= 0){
                cout << " " << fixed << setprecision(4) << correl_AB[i][j];
            } else{
                cout << fixed << setprecision(4) << correl_AB[i][j];
            }
            
            if (j < correl_AB[i].size() - 1) {
                cout << ",";
            }
        }
        if (i == correl_AB.size() - 1){
            cout << "]" << endl;
        } else{
            cout << endl;
        }
    }

    return 0;
}
