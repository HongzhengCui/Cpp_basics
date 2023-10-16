#include "std_lib_facilities.h"

double convertToMeters(double value, std::string unit) {
    if (unit == "m"){
        value = value;
    }    
    else if (unit == "cm") {
        value = value * 1.0 / 100.0;
    } 
    else if (unit == "in") {
        value = value * 2.54 * 1.0 / 100.0;
    } 
    else if (unit == "ft") {
        value = value * 12.0 * 2.54 * 1.0 / 100.0;
    }
    return value;
}

bool isValidUnit(std::string unit) {
    if ((unit == "cm") || (unit == "m") || (unit == "in") || (unit == "ft")){
        return true;
    }
    else{
        return false;
    }
}

int main() {
    std::cout << "Enter a double value and a unit (cm, m, in, ft):\n";

    double sum = 0.0;
    int count = 0;
    double val;
    double msmallest = std::numeric_limits<double>::max();
    double mlargest = std::numeric_limits<double>::min();
    double smallest;
    double largest;
    std::string unit, smallest_unit, largest_unit;
    Vector<double> mvalues;

    while (std::cin >> val >> unit) {
        if (!isValidUnit(unit)) {
            std::cout << "bad unit: " << unit << std::endl;
            continue;
        }

        double mvalue = convertToMeters(val, unit);
        sum += mvalue;
        mvalues.push_back(mvalue);


        if (mvalue <= msmallest) {
            msmallest = mvalue;
            smallest = val;
            smallest_unit = unit;
        }
        
        if (mvalue >= mlargest) {
            mlargest = mvalue;
            largest = val;
            largest_unit = unit;
        }

        std::cout << val << unit;

        if (mvalue == msmallest){
            std::cout << " smallest so far";
        }
        if (mvalue == mlargest){
            std::cout << " largest so far";
        }
        std::cout << std::endl;

        count++;
    }

    if (count > 0) {
        std::cout << "smallest: " << msmallest << std::endl;
        std::cout << "largest: " << mlargest << std::endl;
        std::cout << "number: " << count << std::endl;
        std::cout << "sum: " << sum << std::endl;
    } 
    else {
        std::cout << "No valid entries" << std::endl;
    }

    sort(mvalues.begin(), mvalues.end());
    for (int i = 0; i < mvalues.size(); i++) {
        std::cout << mvalues[i] << std::endl;
    }

    return 0;
}