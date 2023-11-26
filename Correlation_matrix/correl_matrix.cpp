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

double Avg(const vector<double>& rates) {
    double sum = 0;

    for (size_t i = 0; i < rates.size(); i++) {
        sum += rates[i];
    }

    return sum / rates.size();
}

double StdDev(const vector<double>& rates, double average) {
    double sum = 0;

    for (size_t i = 0; i < rates.size(); i++) {
        double diff = rates[i] - average;
        sum += pow(diff, 2);
    }

    return sqrt(sum / (rates.size() - 1));
}

double Cov(const vector<double>& R1, const vector<double>& R2) {
    double cov = 0;
    double avg_R1 = Avg(R1);
    double avg_R2 = Avg(R2);

    for (size_t i = 0; i < R1.size(); i++) {
        cov += (R1[i] - avg_R1) * (R2[i] - avg_R2);
    }

    return cov / R1.size();
}

vector<vector<double>> CorrelMatrix(const vector<vector<double>>& data) {
    size_t dimension = data.size();
    vector<vector<double>> correl_matrix(dimension, vector<double>(dimension, 0));

    for (size_t i = 0; i < dimension; i++) {
        for (size_t j = 0; j < dimension; j++) {
            double covariance = Cov(data[i], data[j]);
            double stdDevR1 = StdDev(data[i], Avg(data[i]));
            double stdDevR2 = StdDev(data[j], Avg(data[j]));

            correl_matrix[i][j] = covariance / (stdDevR1 * stdDevR2);
        }
    }

    return correl_matrix;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " filename.csv" << endl;
        return EXIT_FAILURE;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "The file failed to open. Please input the correct file." << endl;
        return EXIT_FAILURE;
    }

    string line;
    vector<vector<double>> data;
    size_t line_index = 0, column = 0;
    

    while (getline(file, line)) {
        if (line_index > 0) {
            stringstream s(line);
            string element;

            getline(s, element, ',');
            data.push_back(vector<double>());
            double value = 0;

            for (size_t i = 0; getline(s, element, ','); i++) {
                if (line_index == 1){
                    if (element == "null"){
                        cerr << "The first data record should be valid." << endl;
                        return EXIT_FAILURE;
                    } else{
                        value = stod(element);
                    }
                } else{
                    if (element == "null"){
                        value = data[line_index - 2][i];
                    } else{
                        value = stod(element);
                    }    
                }
                data[line_index - 1].push_back(value);
            }
        }    
        else{
            stringstream s(line);
            string element;
            for (size_t i = 0; getline(s, element, ','); i++) {
                column++;
                if (i > 0){
                    cout << element << endl;
                }
            }
        }
        line_index++;
    }

    for (size_t i = 0; i < line_index - 1; i++){
        if (data[i].size() + 1 != column){
            cerr << "The file data size is not corret. Please check the header columns." << endl;
            return EXIT_FAILURE;
        }
    }

    vector<vector<double>> total_rates;

    for (size_t j = 0; j < column - 1; j++) {
        vector<double> rates;
        for (size_t i = 1; i < line_index - 1; i++) {
            double rate = data[i][j] / data[i-1][j] - 1;
            rates.push_back(rate);
        }
        total_rates.push_back(rates);
    }

    vector<vector<double>> correl_AB = CorrelMatrix(total_rates);
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