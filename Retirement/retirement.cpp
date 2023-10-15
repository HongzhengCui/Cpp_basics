#include "std_lib_facilities.h"

class RetireInfo {
    public:
    int months;
    double contribution;
    double rate_of_return;
};

void retirement (int startAge, double initial, RetireInfo working, RetireInfo retired){
    double balance = initial;
    int years = startAge / 12;
    int months = startAge % 12;
    cout << "Age " << setw(3) << years << " month " << setw(2) << months << " you have $" << fixed << setprecision(2) << balance << "\n";
    
    for (int i = startAge + 1; i < startAge + working.months + retired.months; i++){
        if (i <= startAge + working.months){
            balance = balance + balance * working.rate_of_return + working.contribution;
            int years = i / 12;
            int months = i % 12;
            cout << "Age " << setw(3) << years << " month " << setw(2) << months << " you have $" << fixed << setprecision(2) << balance << "\n";
        }
        else{
            balance = balance + balance * retired.rate_of_return + retired.contribution;
            int years = i / 12;
            int months = i % 12;
            cout << "Age " << setw(3) << years << " month " << setw(2) << months << " you have $" << fixed << setprecision(2) << balance << "\n";
        }
    }
}

int main() {
    RetireInfo working;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045/12;

    RetireInfo retired;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01/12;
    
    retirement(327, 21345, working, retired);
}
