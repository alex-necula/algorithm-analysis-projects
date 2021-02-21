// Copyright 2020
// Authors: Radu Nichita, Matei Simtinică

#ifndef BONUS_H_
#define BONUS_H_

#include "task.h"

/*
 * Bonus Task
 * You have to implement 4 methods:
 * read_problem_data - read the problem input and store it however you see fit
 * formulate_oracle_question - transform the current problem instance into a SAT instance and write the oracle input 
 * decipher_oracle_answer - transform the SAT answer back to the current problem's answer
 * write_answer - write the current problem's answer
 */
class Bonus : public Task {
   private:
    int relationships_num;
    int families_num;
    std::vector<std::pair<int, int>> relationships;
    std::vector<int> minimum_extended_family;  // Minimum vertex cover

   public:
    void solve() override {
        read_problem_data();
        formulate_oracle_question();
        ask_oracle();
        decipher_oracle_answer();
        write_answer();
    }

    void read_problem_data() override {
        std::ifstream input(in_filename);

        input >> families_num >> relationships_num;
        for (int i = 0; i < relationships_num; i++) {
            int a, b;
            input >> a >> b;
            relationships.push_back(std::make_pair(a, b));
        }
    }

    void formulate_oracle_question() {
        // Reducing Vertex Cover to SAT
        std::ofstream oracle(oracle_in_filename);

        int top = families_num + 1;  // hard clause weight
        int clauses_num = relationships_num + families_num;

        oracle << "p wcnf " << families_num << " " << clauses_num << " " << top << std::endl;

        // Let variable x_i for every node i, representing the condition that
        // the node is part of the vertex cover.

        // Constraint: all edges are covered
        for (auto& relationship : relationships) {
            oracle << top << " " << relationship.first << " " << relationship.second << " 0"
                   << std::endl;
        }

        // Soft clause: each variable corresponding to node is false
        for (int i = 1; i <= families_num; i++) {
            oracle << "1 " << -i << " 0" << std::endl;
        }
    }

    void decipher_oracle_answer() {
        std::ifstream answer(oracle_out_filename);
        int variable, variables_num, true_variables_num;

        answer >> variables_num >> true_variables_num;

        for (int i = 0; i < variables_num; i++) {
            answer >> variable;
            if (variable > 0) {
                minimum_extended_family.push_back(variable);
            }
        }
    }

    void write_answer() override {
        std::ofstream output(out_filename);
        for (int& family : minimum_extended_family) {
            output << family << " ";
        }
    }
};

#endif  // BONUS_H_
