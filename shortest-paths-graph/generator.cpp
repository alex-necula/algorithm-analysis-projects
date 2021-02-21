#include <bits/stdc++.h>
#include <iostream>

#define MAXWEIGHT 200
#define MAX_TEST_NAME_SIZE 32

int main() {
    std::set<std::pair<int, int>> container;
    std::set<std::pair<int, int>>::iterator it;

    char input_test[MAX_TEST_NAME_SIZE];
    int V = 0, E = 0, tests_no, first_test_index;
    std::string type;

    // For random values every time
    srand(time(NULL));

    std::cout << "Enter graph type (sparse/dense/random)\n";
    std::cin >> type;

    while (type != "dense" && type != "sparse" && type != "random") {
        std::cout << "Invalid graph type. Please input dense, sparse or random\n";
        std::cin >> type;
    }

    if (type == "dense") {
        std::cout << "Enter number of vertices\n";
        std::cin >> V;
        E = V * (V - 1) * 0.9;
    } else if (type == "sparse") {
        std::cout << "Enter number of vertices\n";
        std::cin >> V;
        E = V * (V - 1) * 0.1;
    } else {
        V = 10 + (rand() % static_cast<int>(1000 - 10 + 1));
    }

    std::cout << "Enter number of tests" << std::endl;
    std::cin >> tests_no;
    std::cout << "Enter index of first test" << std::endl;
    std::cin >> first_test_index;

    int last_test_index = tests_no + first_test_index;

    for (int i = first_test_index; i < last_test_index; i++) {
        sprintf(input_test, "./other_tests/in/test%d.in", i);
        std::ofstream file(input_test);
        if (file.fail()) {
            std::cout << "Failed to write test" << i << ".in" << std::endl;
        }
        if (type == "random") {
            E = V * (V - 1) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
        }

        // First print the number of vertices and edges
        file << V << " " << E << std::endl;

        // Then print the edges of the form (a b)
        // where 'a' is connected to 'b'
        for (int j = 0; j < E; j++) {
            int a = 1 + rand() % V;
            int b = 1 + rand() % V;
            std::pair<int, int> p = std::make_pair(a, b);

            // Search for a random "new" edge every time
            while (container.find(p) != container.end()) {
                a = 1 + rand() % V;
                b = 1 + rand() % V;
                p = std::make_pair(a, b);
            }
            container.insert(p);
        }

        for (it = container.begin(); it != container.end(); ++it) {
            int wt = 1 + rand() % MAXWEIGHT;
            file << it->first << " " << it->second << " " << wt << std::endl;
        }

        container.clear();
    }

    return 0;
}