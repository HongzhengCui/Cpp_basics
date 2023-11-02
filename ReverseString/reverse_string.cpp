#include <vector>
#include <string>
#include <iostream>
using namespace std;

void reverse(string &str) {
    int left = 0;
    int right = str.length() - 1;

    while (left < right) {
        swap(str[left], str[right]);
        left++;
        right--;
    }
}

int main(void) {
    vector<string> strings;

    strings.push_back("");
    strings.push_back("123");
    strings.push_back("abcd");
    strings.push_back("Captain's log, Stardate 42523.7");
    strings.push_back("Hello, my name is Inigo Montoya.");
    strings.push_back("You can be my wingman anyday!");
    strings.push_back("Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!");
    strings.push_back("amanap lanac a nalp a nam a");


    for (string test: strings) {
        reverse(test);
        cout << test << endl;
    }

    return EXIT_SUCCESS;
}