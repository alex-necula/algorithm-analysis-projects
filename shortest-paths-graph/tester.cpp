#include <errno.h>
#include <limits.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include "algo.h"

const int MAX_TEST_NAME_SIZE = 32;

namespace std {

/**
 * Prints a given 2D matrix represented as a vector of vectors to a file.
 * If element is INT_MAX, print it as inf.
 */
int print_output(const char* output_file, const vector<vector<int>> matrix) {
    ofstream file(output_file);
    if (file.fail()) {
        return -1;
    }

    for (unsigned int i = 0; i < matrix.size(); i++) {
        for (unsigned int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != INT_MAX) {
                file << matrix[i][j] << " ";
            } else {
                file << "inf ";
            }
        }
        file << endl;
    }

    return 0;
}

int parse_input(const char* input_file, vector<vector<edge>>& input) {
    int V, E;
    int x, y, z;

    ifstream file(input_file);
    if (file.fail()) {
        return -1;
    }

    /* Parse input */
    if (!(file >> V >> E)) {
        return -1;
    }

    /* Allocate memory */
    input.resize(V);

    for (int i = 0; i < E; i++) {
        if (!(file >> x >> y >> z)) {
            return -1;
        }
        // Internally, vertice's index start from 0
        x--;
        y--;
        input[x].push_back(make_pair(y, z));
    }

    return 0;
}

int parse_ref(const char* reference_file, vector<vector<int>>& ref) {
    ifstream file(reference_file);
    if (file.fail()) {
        return -1;
    }

    int V = ref.size();

    /* Parse ref */
    string elem;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (file >> elem) {
                if (elem == "inf") {
                    ref[i][j] = INT_MAX;
                } else {
                    ref[i][j] = stoi(elem);
                }
            } else {
                return -1;
            }
        }
    }

    return 0;
}

int run_test(const char* input_file, const char* reference_file,
             const char* output_file, unsigned int* time, bool check_ref) {
    int rc; /* return code */
    vector<vector<edge>> input;

    /* Parse test data */
    rc = parse_input(input_file, input);
    if (rc) {
        cerr << "Invalid input file\n";
        return -1;
    }

    /* Call algorithm and count time*/
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> output = shortest_path_all(input);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    *time = duration.count();

    /* Print output */
    rc = print_output(output_file, output);
    if (rc) {
        cerr << "Cannot write output file\n";
        return -1;
    }

    if (check_ref) {
        /* Parse reference data */
        int V = input.size();
        vector<vector<int>> ref(V, vector<int>(V));
        rc = parse_ref(reference_file, ref);
        if (rc) {
            cerr << "Invalid reference file\n";
            return -1;
        }

        /* Check answer */
        if (output == ref) {
            cout << "PASSED\n";
        } else {
            cout << "FAILED\n";
        }
    }

    return 0;
}
}  // namespace std

int main() {
    char input_test[MAX_TEST_NAME_SIZE], reference_file[MAX_TEST_NAME_SIZE],
        output_file[MAX_TEST_NAME_SIZE];
    unsigned int time, first, last, tests_no;
    bool check_ref;
    char type;

    std::cout << "Do you want to check manual (m) or computer generated (g) tests?\n";
    std::cin >> type;

    while (type != 'm' && type != 'g') {
        std::cout << "Invalid. Please input m or g\n";
        std::cin >> type;
    }

    check_ref = (type == 'm') ? true : false;

    std::cout << "Please enter indexes of the first and the last test separated by space\n";
    std::cin >> first >> last;

    while (first > last) {
        std::cout << "Invalid. First is larger than last\n";
        std::cin >> first >> last;
    }

    tests_no = last - first + 1;
    std::vector<unsigned int> total_time(tests_no);

    for (unsigned int i = first; i <= last; i++) {
        if (check_ref) {
            sprintf(input_test, "./in/test%d.in", i);
            sprintf(output_file, "./out_testing/test%d.out", i);
            sprintf(reference_file, "./out/test%d.out", i);
            std::cout << "Running test " << i << " ................. ";
        } else {
            sprintf(input_test, "./other_tests/in/test%d.in", i);
            sprintf(output_file, "./other_tests/out/test%d.out", i);
        }

        if (std::run_test(input_test, reference_file, output_file, &time, check_ref)) {
            std::cerr << "Failed to run test " << i << std::endl;
            return -1;
        }

        total_time.push_back(time);
    }
    unsigned int sum = std::accumulate(total_time.begin(), total_time.end(), 0);
    std::cout << "Average time for running a test was " << (float)sum / tests_no << " ms\n";

    return 0;
}
