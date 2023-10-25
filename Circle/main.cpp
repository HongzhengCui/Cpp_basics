#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

#include "circle.hpp"

using namespace std;

/**
 * @Brief moves a particular Circle's center by an adjustment value
 *  Circle object updated in place.
 *  
 * @param reference to a vector of Circle objects
 * @param arguments, string of number that function as the
 *        identifier for the circle(an int) and the dx,dy
 *        offset (doubles) to move the point. If
 *        additional / wrong arguments specified, no action
 *        is taken except a message sent to cerr  
 */
void doMove(vector<Circle> &circles, string arguments) {
    stringstream sinput(arguments);

    size_t circle_num = std::numeric_limits<unsigned>::max();
    double dx = 0.0; 
    double dy = 0.0;

    if (not (sinput >> circle_num >> dx >> dy)) {
        cerr << "Incorrect arguments for move: " << arguments << endl;
        return;
    }
    if (not (sinput.peek() == EOF)) {
        cerr << "Extraneous input on line: " << arguments << endl;
        return;
    }
    if ( circle_num >= circles.size()) {
        cerr << "Invalid valid value for circle #: " << circle_num << endl;
    }
    circles[circle_num].move(dx, dy);
}

/**
 * @brief computes the intersection area between two circles
 *        Messsage written to standard out (cout)
 * 
 * @param reference to a vector of Circle objects
 * @param arguments string containing two integer numbes that specify the two
 *        circles to compute the intersections area between them. If
 *        additional / wrong arguments specified, no action
 *        is taken except a message sent to cerr
 */
void doIntersection(vector<Circle> circles, string arguments) {
  stringstream sinput(arguments);

  size_t c1 = std::numeric_limits<unsigned>::max();
  size_t c2 = std::numeric_limits<unsigned>::max();

  if ( not (sinput >> c1 >> c2)) {
      cerr << "Incorrect arguments for intersection: " << arguments << endl;
      return;
  }
  if (not (sinput.peek() == EOF)) {
      cerr << "Extraneous input on line: " << arguments << endl;
      return;
  }
  if (c1 >= circles.size()) {
      cerr << "Invalide valid value for circle #1: "<< c1 << endl;
      return;
  }
  if (c2 >= circles.size()) {
      cerr << "Invalide valid value for circle #2: "<< c2 << endl;
      return;
  }

  double area = circles[c1].intersectionArea(circles[c2]);
  cout << "Area of intersection between c" << c1 << " and c" << c2 << ": " << fixed << setprecision(2) << setw(5) << area << endl;
}


/**
 * @brief Converts a string to an integer
 *        
 * Will output messages to stderr on bad conversions
 * 
 * @returns converted integer value, UINT_MAX on error 
 */
unsigned int convertStringToUnsignedInt(const string &input) {
    try {
        unsigned long result = std::stoul(input);
        if (result > std::numeric_limits<unsigned>::max()) {
            throw std::out_of_range("stou");
        }
        return result;
    }
    catch (exception &err) {
        cerr << "Conversion failure: " << input << endl;
        std::cerr << "Error occurred: " << err.what() << std::endl;
        return std::numeric_limits<unsigned>::max();
    }
}

// trim functions
// source https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
/**
 * @brief removes any whitespace from the left-side of a string. performed in-place 
 */
string& ltrim(string& s, const char* t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

/**
 * @brief removes any whitespace from the right-side of a string. performed in-place 
 */
string& rtrim(string& s, const char* t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

/**
 * @brief removes any whitespace from the left and side of a string. performed in-place 
 */
string& trim(string& s, const char* t = " \t\n\r\f\v") {
    return ltrim(rtrim(s, t), t);
}

//input:
//numpoints  (an int)
//0 or more commands:
// m pnum dx dy    move point pnum by (dx,dy)
// d p1 p2         print the distance between points p1 and p2

/**
 * @brief uses the point class
 * 
 * input: 
 *   numpoints  (an int)
 *   0 or more commands:
 *     m cnum dx dy    move circle cnum by (dx,dy)
 *     i c1 c2         print the are of intersections between circles c1 and c2
 */
int main(void) {
    string line = "";
    size_t numCircles = 0;

    cout << "Enter the number of circles to create: ";
    if (getline(cin,line)) {
         numCircles = convertStringToUnsignedInt(line);
    }
    if (numCircles <= 0 || numCircles == std::numeric_limits<unsigned>::max()) {
        cerr << "Number of circles must be an integer >= 0\n" << "Received: " << line << endl;
        return EXIT_FAILURE;
    }
    cout << numCircles << endl;

    vector<Circle> circles;
    for (auto i = 0U; i < numCircles; i++) {
        double radius = 0.0, x = 0.0, y = 0.0;
        if (cin >> x >> y >> radius ) {
            Point p;
            p.move(x,y);
            Circle c(p,radius);
            circles.push_back(c);
        }
        else {
            cerr << "Unexpected input issue" << endl;
            return EXIT_FAILURE;
        }
    }
     
     while (getline(cin, line)) {
         line = trim(line);
         if (line.length() == 0) {
             continue;
         }
         switch (line[0]) {
             case 'm': doMove(circles, line.substr(1));
                       break;
             case 'i': doIntersection(circles, line.substr(1));
                       break;
             default: cerr <<  "Unrecognized command: " << line << endl;
         }
    }

    return EXIT_SUCCESS;
}
