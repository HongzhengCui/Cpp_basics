#include "asset.hpp"
#include <cmath>

// Calculate the average of the rates vector
double Avg(const std::vector<double>& rates) {
    double total = 0;

    for (size_t i = 0; i < rates.size(); i++) {
        total += rates[i];
    }

    double avg = total / rates.size();

    return avg;
}

// Calculate the standard deviation of the rates vector
double StdDev(const std::vector<double>& rates, double average) {
    double total = 0;

    for (size_t i = 0; i < rates.size(); i++) {
        total += (rates[i] - average) * (rates[i] - average);
    }

    double StdDev = sqrt(total / (rates.size() - 1));
    return StdDev;
}

// Calculate the each covariance
double Cov(const std::vector<double>& R1, const std::vector<double>& R2, double avg_R1, double avg_R2) {
    double cov = 0;

    for (size_t i = 0; i < R1.size(); i++) {
        cov += (R1[i] - avg_R1) * (R2[i] - avg_R2);
    }

    return cov / R1.size();
}

// Calculate the correlation matrix
std::vector<std::vector<double>> CorrelMatrix(const std::vector<std::vector<double>>& dataset) {
    size_t dimension = dataset.size();
    std::vector<std::vector<double>> correl_matrix(dimension, std::vector<double>(dimension, 0));

    for (size_t i = 0; i < dimension; i++) {
        for (size_t j = 0; j < dimension; j++) {
            double covariance = Cov(dataset[i], dataset[j], Avg(dataset[i]), Avg(dataset[j]));
            double stdDevR1 = StdDev(dataset[i], Avg(dataset[i]));
            double stdDevR2 = StdDev(dataset[j], Avg(dataset[j]));

            correl_matrix[i][j] = covariance / (stdDevR1 * stdDevR2);
        }
    }

    return correl_matrix;
}