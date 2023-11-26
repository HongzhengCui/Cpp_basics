#include <vector>

double Avg(const std::vector<double>& rates);
double StdDev(const std::vector<double>& rates, double average);
double Cov(const std::vector<double>& R1, const std::vector<double>& R2, double avg_R1, double avg_R2);
std::vector<std::vector<double>> CorrelMatrix(const std::vector<std::vector<double>>& data);
