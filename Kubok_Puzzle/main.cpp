#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Print the result according to the expected format
void printBoard(vector<vector<int>> &board, vector<int> row_sums, vector<int>col_sums) {
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (i == 0 && j == 0) {cout << "   ";}
            else if (i == 0 && j != 0)
            {
                if (col_sums[j - 1] < 10) {cout << "  " << col_sums[j - 1];}
                else {cout << " " << col_sums[j - 1];}
            }
            else if (i != 0 && j == 0) 
            {
                if (row_sums[i - 1] < 10) {cout << "  " << row_sums[i - 1];}
                else {cout << " " << row_sums[i - 1];}
            }
            else 
            {
                if (board[i - 1][j - 1] < 10) {cout << "  " << board[i - 1][j - 1];}
                else {cout << " " << board[i - 1][j -1];}
            }
        }
        cout << endl;
    }
}

bool isValid(vector<vector<int>>& board, int row, int col, int num, vector<int> row_sums, vector<int> col_sums) {
    // Check if the number already exists
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }

    // Calculate the sum of the row
    int calc_sum_row = 0;
    for (int j = 0; j < 4; ++j) {
        calc_sum_row += board[row][j];
    }
    calc_sum_row += num;

    // Check if the row is fully filled
    bool row_is_full;
    for (int j = 0; j < 4; ++j) {
        if (board[row][j] == 0 && j != col) {
            row_is_full = false;
            break;
        } else {
            row_is_full = true;
        }
    }

    // Check if the sum of the row is equal to the expected when the row is fully filled
    if (row_is_full && calc_sum_row != row_sums[row]) {
        return false;
    }

    // Calculate the sum of the column
    int calc_sum_col = 0;
    for (int i = 0; i < 4; ++i) {
        calc_sum_col += board[i][col];
    }
    calc_sum_col += num;

    // Check if the column is fully filled
    bool col_is_full;
    for (int i = 0; i < 4; ++i) {
        if (board[i][col] == 0 && i != row) {
            col_is_full = false;
            break;
        } else {
            col_is_full = true;
        }
    }

    // Check if the sum of the column is equal to the expected when the column is fully filled
    if (col_is_full && calc_sum_col != col_sums[col]) {
        return false;
    }

    return true;
}

bool solve_kubok(vector<vector<int>>& board, const vector<int> row_sums, const vector<int> col_sums) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Traverse the grid and find the "empty" locations
            if (board[i][j] == 0) {
                // Exhaustion
                for (int num = 1; num <= 16; ++num) {
                    if (isValid(board, i, j, num, row_sums, col_sums)) {
                        board[i][j] = num;
                        // Recursion
                        if (solve_kubok(board, row_sums, col_sums)) {
                            return true;
                        }
                        board[i][j] = 0; // Backtracking
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Please input one filename at the command line." << endl;
        return EXIT_FAILURE;
    }

    string expert = argv[1];

    // PARSE EXPERT
    ifstream in(expert);
    if (!in.is_open()) {
        cerr << "Unable to open " << expert << endl;
        return EXIT_FAILURE;
    }

    string line;
    vector<vector<int>> board;
    vector<int> sums;

    // Read the first two lines: row sums and column sums
    for (size_t i = 0; getline(in, line); ++i) {
        if (i <= 1) {
            vector<string> fields;
            string field;
            string sum;

            istringstream ss(line);
            while (getline(ss, field, ' ')) {
                fields.push_back(field);
                if (fields.size() == 3) {
                    istringstream s(fields[2]);
                    while (getline(s, sum, ',')) {
                        try {
                            sums.push_back(stoi(sum));
                        } catch (...) {
                            cerr << "The sums cannot be imported as integers." << endl;
                            return EXIT_FAILURE;
                        }
                    }
                }
            }
        }

        // Read the original grid
        else if (i >= 3) {
            vector<int> values;
            istringstream ss(line);
            string value;
            while (getline(ss, value, ',')) {
                try {
                    values.push_back(stoi(value));
                } catch (...) {
                    cerr << "The values on the board cannot be imported as integers." << endl;
                    return EXIT_FAILURE;
                }
            }
            board.push_back(values);
        }
    }   
    in.close();

    if (sums.size() != 8) {
        cerr << "The sums does not have 8 values." << endl;
        return EXIT_FAILURE;
        }

    vector<int> col_sums(sums.begin(), sums.begin() + 4);
    vector<int> row_sums(sums.begin() + 4, sums.begin() + 8);

    // Detect errors from the board
    if (board.size() != 4) {
        cerr << "The board does not have four rows." << endl;
        return EXIT_FAILURE;
        }

    for (size_t i = 0; i < 4; ++i) {
        if (board[i].size() != 4){
            cerr << "The board does not have four columns." << endl;
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < 4; ++j) {
            if ((board[i][j] < 1 && board[i][j] != 0) || board[i][j] > 16){
                cerr << "The numbers on the board are out of the range." << endl;
                return EXIT_FAILURE;
            }
        }
    }

    // Detect errors from the row sums
    for (size_t i = 0; i < 4; ++i) {
        if (row_sums[i] < 10 || row_sums[i] > 58) {
            cerr << "The row sums are out of the range." << endl;
            return EXIT_FAILURE;
        }
    }
    // Detect errors from the column sums
    for (size_t i = 0; i < 4; ++i) {
        if (col_sums[i] < 10 || col_sums[i] > 58) {
            cerr << "The column sums are out of the range." << endl;
            return EXIT_FAILURE;
        }
    }

    if (solve_kubok(board, row_sums, col_sums)) {
        printBoard(board, row_sums, col_sums);
    }
    else {
        cout << "There is no solution of the board." << endl;
    }

    return EXIT_SUCCESS;
}
