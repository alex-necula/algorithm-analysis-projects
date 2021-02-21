// Copyright 2020
// Authors: Radu Nichita, Matei Simtinică

#ifndef TASK1_H_
#define TASK1_H_

#include <vector>
#include "task.h"

/*
 * Task1
 * You have to implement 4 methods:
 * read_problem_data         - read the problem input and store it however you see fit
 * formulate_oracle_question - transform the current problem instance into a SAT instance and write the oracle input
 * decipher_oracle_answer    - transform the SAT answer back to the current problem's answer
 * write_answer              - write the current problem's answer
 */
class Task1 : public Task {
   private:
    int relationships_num;
    int spies_num;
    int families_num;
    std::vector<std::pair<int, int>> relationships;
    std::vector<int> variables;  // IDs corresponding to variables from solver

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

        input >> families_num >> relationships_num >> spies_num;
        for (int i = 0; i < relationships_num; i++) {
            int a, b;
            input >> a >> b;
            relationships.push_back(std::make_pair(a, b));
        }
    }

    void formulate_oracle_question() {
        std::ofstream oracle(oracle_in_filename);

        int variables_num = spies_num * families_num;
        int clauses_num = 2 * families_num + relationships_num * spies_num;
        oracle << "p cnf " << variables_num << " " << clauses_num << std::endl;

        /* We assign a variable for each family-spy association
         * For example, families_num = 3, spies_num = 2
         * f1-s1, f1-s2, f2-s1, f2-s2, f3-s1, f3-s2
         *   1  ,   2  ,   3  ,   4  ,   5  ,   6
         */

        // Create clauses to choose a different spy in related families
        for (auto& relationship : relationships) {
            for (int spy_id = 1; spy_id <= spies_num; spy_id++) {
                int first_variable_id = (relationship.first - 1) * spies_num + spy_id;
                int second_variable_id = (relationship.second - 1) * spies_num + spy_id;
                oracle << -first_variable_id << " " << -second_variable_id << " 0" << std::endl;
            }
        }

        // Create clauses to choose at least one spy for each family
        for (int family_id = 1; family_id <= families_num; family_id++) {
            for (int spy_id = 1; spy_id <= spies_num; spy_id++) {
                oracle << (family_id - 1) * spies_num + spy_id << " ";
            }
            oracle << "0" << std::endl;
        }

        // Create clauses to choose maximum one spy for each family
        for (int family_id = 1; family_id <= families_num; family_id++) {
            for (int spy_id = 1; spy_id <= spies_num; spy_id++) {
                oracle << -((family_id - 1) * spies_num + spy_id) << " ";
            }
            oracle << "0" << std::endl;
        }
    }

    void decipher_oracle_answer() {
        std::ifstream answer(oracle_out_filename);
        std::string validity;
        answer >> validity;
        if (validity == "True") {
            int variable;
            answer >> variable;  // ignore number of variables
            for (int i = 0; i < spies_num * families_num; i++) {
                answer >> variable;
                if (variable > 0) {
                    variables.push_back(variable);
                }
            }
        }
    }

    void write_answer() override {
        std::ofstream output(out_filename);
        if (variables.empty()) {
            output << "False";
        } else {
            output << "True" << std::endl;
            int family_id = 1;
            for (int& variable : variables) {
                output << variable - (family_id - 1) * spies_num << " ";
                family_id++;
            }
        }
    }
};

#endif  // TASK1_H_
