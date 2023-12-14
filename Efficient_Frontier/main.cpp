#include <iostream>
#include <cstdlib>    
#include <fstream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>
#include "portfolio.hpp"
#include "parse.hpp"
using namespace std;
using namespace Eigen;

int main(int argc, char ** argv) {
    // Decide the unrestricted or restricted case
    if (argc != 3 && argc != 4) {
        cerr << "Please check the number of arguments at the command line." << endl;
        return EXIT_FAILURE;
    }

    // Unrestricted case
    if (argc == 3) {
        vector<string> asset_name;
        vector<double> average_rate_of_return;
        vector<double> standard_deviation;
        vector<vector<double>> correlation_vectors;
        bool restricted_condition = false;

        read_universe(argv[1], asset_name, average_rate_of_return, standard_deviation);
        read_correlation(argv[2], correlation_vectors);

        MatrixXd covariance_matrix = calc_covariance_matrix(standard_deviation, correlation_vectors);
        print_volatility(26, covariance_matrix, average_rate_of_return, restricted_condition);
        return EXIT_SUCCESS;
    }

    // Restricted case
    if (argc == 4) {
        if (strcmp(argv[1], "-r") != 0) {
            cerr << "The optional argument input should be 'r' at the command line." << endl;
            return EXIT_FAILURE;
        }

        vector<string> asset_name;
        vector<double> average_rate_of_return;
        vector<double> standard_deviation;
        vector<vector<double>> correlation_vectors;
        bool restricted_condition = true;

        read_universe(argv[2], asset_name, average_rate_of_return, standard_deviation);
        read_correlation(argv[3], correlation_vectors);

        MatrixXd covariance_matrix = calc_covariance_matrix(standard_deviation, correlation_vectors);
        print_volatility(26, covariance_matrix, average_rate_of_return, restricted_condition);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
};