#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <Eigen/Dense>
#include <vector>

Eigen::VectorXd vector_conversion(const std::vector<double>& vector_1D);
Eigen::MatrixXd vectors_to_matrix_2D(const std::vector<std::vector<double>>& vectors_2D);
std::vector<std::vector<double>> diagonalization(const std::vector<double>& vector_1D);
Eigen::MatrixXd calc_covariance_matrix(const std::vector<double>& standard_deviation, const std::vector<std::vector<double>>& correlation_vectors);
Eigen::MatrixXd lagrange_matrix_conversion(const Eigen::MatrixXd& covariance_matrix, const std::vector<double>& average_rate_of_return);
Eigen::VectorXd lagrange_vector_conversion(const Eigen::MatrixXd& covariance_matrix, double expected_return);
Eigen::VectorXd calc_optimal_weights(const Eigen::MatrixXd& lagrange_matrix, const Eigen::VectorXd& lagrange_vector, const Eigen::MatrixXd& covariance_matrix);
double calc_volatility(const Eigen::VectorXd& optimal_weights, const Eigen::MatrixXd& covariance_matrix);
std::vector<size_t> negative_location(const Eigen::VectorXd& optimal_weights);
Eigen::MatrixXd reconstruct_lagrange_matrix(const Eigen::MatrixXd& lagrange_matrix, const std::vector<size_t>& negative_index);
Eigen::VectorXd reconstruct_lagrange_vector(const Eigen::VectorXd& lagrange_vector, const std::vector<size_t>& negative_index);
void print_volatility(int expected_number, const Eigen::MatrixXd& covariance_matrix, const std::vector<double>& average_rate_of_return, bool restricted_condition);

#endif
