#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>
#include "portfolio.hpp"
#include "parse.hpp"

// Convert STL vector to Eigen vector
Eigen::VectorXd vector_conversion(const std::vector<double>& vector_1D) {
    size_t N = vector_1D.size();
    Eigen::VectorXd eigen_vector(N);

    for (size_t i = 0; i < N; ++i) {
        eigen_vector(i) = vector_1D[i];
    }
    return eigen_vector;
}

// Convert 2D vector to Eigen matrix
Eigen::MatrixXd vectors_to_matrix_2D(const std::vector<std::vector<double>>& vectors_2D) {
    size_t rows = vectors_2D.size();
    size_t cols = vectors_2D[0].size();

    Eigen::MatrixXd matrix_2D(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix_2D(i, j) = vectors_2D[i][j];
        }
    }

    return matrix_2D;
}

// Diagonalize the 1D vector to 2D vector
std::vector<std::vector<double>> diagonalization(const std::vector<double>& vector_1D) {
    std::vector<std::vector<double>> diag_matrix(vector_1D.size(), std::vector<double>(vector_1D.size(), 0.0));

    for (std::size_t i = 0; i < vector_1D.size(); ++i) {
        diag_matrix[i][i] = vector_1D[i];
    }

    return diag_matrix;
}

// Calculate the covariance matrix
Eigen::MatrixXd calc_covariance_matrix(const std::vector<double>& standard_deviation, const std::vector<std::vector<double>>& correlation_vectors) {
    std::vector<std::vector<double>> diag_standard_deviation_vectors = diagonalization(standard_deviation);
    Eigen::MatrixXd diag_standard_deviation_matrix = vectors_to_matrix_2D(diag_standard_deviation_vectors);
    Eigen::MatrixXd correlation_matrix = vectors_to_matrix_2D(correlation_vectors);
    Eigen::MatrixXd covariance_matrix = diag_standard_deviation_matrix * correlation_matrix * diag_standard_deviation_matrix;

    return covariance_matrix;
}

// Form the lagrange matrix (left-hand side)
Eigen::MatrixXd lagrange_matrix_conversion(const Eigen::MatrixXd& covariance_matrix, const std::vector<double>& average_rate_of_return) {
    Eigen::VectorXd average_rate_of_return_vector = vector_conversion(average_rate_of_return);
    std::size_t N = covariance_matrix.rows();

    Eigen::MatrixXd lagrange_matrix = Eigen::MatrixXd::Zero(N + 2, N + 2);
    lagrange_matrix.block(0, 0, N, N) = covariance_matrix;
    lagrange_matrix.block(0, N, N, 1) = Eigen::VectorXd::Ones(N);
    lagrange_matrix.block(0, N + 1, N, 1) = average_rate_of_return_vector;
    lagrange_matrix.block(N, 0, 1, N) = Eigen::VectorXd::Ones(N).transpose();
    lagrange_matrix.block(N + 1, 0, 1, N) = average_rate_of_return_vector.transpose();

    return lagrange_matrix;
}

// Form the lagrange vector (right-hand side)
Eigen::VectorXd lagrange_vector_conversion(const Eigen::MatrixXd& covariance_matrix, double expected_return) {
    std::size_t N = covariance_matrix.rows();
    
    Eigen::VectorXd lagrange_vector = Eigen::VectorXd::Zero(N + 2);
    lagrange_vector(N) = 1.0;
    lagrange_vector(N + 1) = expected_return;
    return lagrange_vector;
}

// Calculate the optimal weights by the lagrange method
Eigen::VectorXd calc_optimal_weights(const Eigen::MatrixXd& lagrange_matrix, const Eigen::VectorXd& lagrange_vector, const Eigen::MatrixXd& covariance_matrix) {
    Eigen::VectorXd result = lagrange_matrix.fullPivHouseholderQr().solve(lagrange_vector);
    size_t N = covariance_matrix.rows();
    Eigen::VectorXd optimal_weights = result.head(N);
    return optimal_weights;
}

// Calculate the volatility
double calc_volatility(const Eigen::VectorXd& optimal_weights, const Eigen::MatrixXd& covariance_matrix) {
    double volatility = std::sqrt(optimal_weights.transpose() * covariance_matrix * optimal_weights);
    return volatility;
}

// Find where the optimal weight is negative
std::vector<size_t> negative_location(const Eigen::VectorXd& optimal_weights) {
    std::vector<size_t> negative_index;
    for (size_t i = 0; i < static_cast<size_t>(optimal_weights.size()); ++i) {
        if (optimal_weights(i) < -1e-12) {
            negative_index.push_back(i);
        }
        /*The value is set to 0.1%, which is relatively high. However, when I set it to -1e-12, 
        my program get stuck and only output the first fourteen volalities.*/
    }
    return negative_index;
}

// Reconstruct the lagrange matrix for avoiding short selling
Eigen::MatrixXd reconstruct_lagrange_matrix(const Eigen::MatrixXd& lagrange_matrix, const std::vector<size_t>& negative_index) {
    size_t N = lagrange_matrix.rows() - 2;
    Eigen::MatrixXd lagrange_matrix_new = Eigen::MatrixXd::Zero(N + 2 + negative_index.size(), N + 2 + negative_index.size());

    lagrange_matrix_new.block(0, 0, N + 2, N + 2) = lagrange_matrix.block(0, 0, N + 2, N + 2);

    for (size_t i = 0; i < negative_index.size(); ++i) {
        Eigen::VectorXd restricted_addon_vector = Eigen::VectorXd::Zero(N);
        restricted_addon_vector(negative_index[i]) = 1.0;
        lagrange_matrix_new.block(0, N + 2 + i, N, 1) = restricted_addon_vector;
        lagrange_matrix_new.block(N + 2 + i, 0, 1, N) = restricted_addon_vector.transpose();
    }
    return lagrange_matrix_new;
}

// Reconstruct the lagrange vector for avoiding short selling
Eigen::VectorXd reconstruct_lagrange_vector(const Eigen::VectorXd& lagrange_vector, const std::vector<size_t>& negative_index){
    size_t N = lagrange_vector.size() - 2;
    Eigen::VectorXd lagrange_vector_new = Eigen::VectorXd::Zero(N + 2 + negative_index.size());
    lagrange_vector_new.head(N + 2) = lagrange_vector.head(N + 2);
    return lagrange_vector_new;
}

// Print the result according to the required formart
void print_volatility(int expected_number, const Eigen::MatrixXd& covariance_matrix, const std::vector<double>& average_rate_of_return, bool restricted_condition) {
    std::cout << "ROR,volatility" << std::endl;
    for (int i = 1; i < expected_number + 1; ++i) {
        Eigen::MatrixXd lagrange_matrix = lagrange_matrix_conversion(covariance_matrix, average_rate_of_return);
        Eigen::VectorXd lagrange_vector = lagrange_vector_conversion(covariance_matrix, 0.01 * i);
        Eigen::VectorXd optimal_weights= calc_optimal_weights(lagrange_matrix, lagrange_vector, covariance_matrix);

        double volatility;
        if (restricted_condition) {
            std::vector<size_t> negative_index = negative_location(optimal_weights);
            Eigen::MatrixXd lagrange_matrix_new = reconstruct_lagrange_matrix(lagrange_matrix, negative_index);
            Eigen::VectorXd lagrange_vector_new = reconstruct_lagrange_vector(lagrange_vector, negative_index);
            while (!negative_index.empty()) {
                lagrange_matrix_new = reconstruct_lagrange_matrix(lagrange_matrix_new, negative_index);
                lagrange_vector_new = reconstruct_lagrange_vector(lagrange_vector_new, negative_index);
                optimal_weights = calc_optimal_weights(lagrange_matrix_new, lagrange_vector_new, covariance_matrix);
                negative_index = negative_location(optimal_weights);
            }
            volatility = calc_volatility(optimal_weights, covariance_matrix);
        } else {
            volatility = calc_volatility(optimal_weights, covariance_matrix);
        }
        std::cout << i << ".0%," << std::fixed << std::setprecision(2) << volatility * 100 << "%" << std::endl;
    }
}
