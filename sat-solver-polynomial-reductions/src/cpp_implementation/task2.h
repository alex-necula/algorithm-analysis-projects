// Copyright 2020
// Authors: Radu Nichita, Matei Simtinică

#ifndef TASK2_H_
#define TASK2_H_

#include <map>
#include <set>
#include <vector>

#include "task.h"
/*
 * Task2
 * You have to implement 4 methods:
 * read_problem_data         - read the problem input and store it however you see fit
 * formulate_oracle_question - transform the current problem instance into a SAT instance and write the oracle input
 * decipher_oracle_answer    - transform the SAT answer back to the current problem's answer
 * write_answer              - write the current problem's answer
 */
class Task2 : public Task {
   private:
    int relationships_num;
    int families_num;
    int family_size;
    std::vector<std::vector<int>> relationships;  // Adjacency matrix
    std::vector<int> variables;                   // IDs corresponding to variables from solver
    std::map<int, std::pair<int, int>> variable_map;

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

        input >> families_num >> relationships_num >> family_size;

        // Initialize adjacency matrix
        relationships.resize(families_num, std::vector<int>(families_num));

        for (int i = 0; i < relationships_num; i++) {
            int a, b;
            input >> a >> b;
            relationships[a - 1][b - 1] = 1;
            relationships[b - 1][a - 1] = 1;
        }
    }

    void formulate_oracle_question() {
        std::ofstream oracle(oracle_in_filename);
        std::set<std::string> clause_list;  // using set prevents duplicates
        int variable = 1;

        // Reducing K-Clique problem to SAT

        // We create a list of variables which are interpreted as
        // "v is the i-th vertex in the clique"

        // Constraint : there must be exactly one vertex v in that clique
        // for each i between 1 and k (family_size).
        for (int i = 1; i <= family_size; i++) {
            std::string clause;
            for (int v = 0; v < families_num; v++) {
                variable_map[variable] = std::make_pair(i, v);
                clause.append(std::to_string(variable) + " ");
                variable++;
            }
            clause.append("0");
            clause_list.insert(clause);
        }

        for (auto it1 = variable_map.begin(); it1 != variable_map.end(); it1++) {
            int variable1 = it1->first;
            int i = it1->second.first;
            int v = it1->second.second;
            for (auto it2 = variable_map.begin(); it2 != variable_map.end(); it2++) {
                int variable2 = it2->first;
                int j = it2->second.first;
                int w = it2->second.second;

                // Constraint : For every non-edge (v,w), v and w cannot both be in the clique
                if (relationships[v][w] == 0 && v != w && variable1 != variable2) {
                    clause_list.insert(std::string("-") + std::to_string(variable1) + " -" +
                                       std::to_string(variable2) + " 0");
                }

                // Constraint : For every i, j (where j != i),
                // the i-th vertex is different from the j-th vertex
                if (((v == w && i != j) || (v != w && i == j)) && (variable1 != variable2)) {
                    clause_list.insert(std::string("-") + std::to_string(variable1) + " -" +
                                       std::to_string(variable2) + " 0");
                }
            }
        }

        int variables_num = variable_map.size();
        int clauses_num = clause_list.size();
        oracle << "p cnf " << variables_num << " " << clauses_num << std::endl;

        for (auto& clause : clause_list) {
            oracle << clause << std::endl;
        }
    }

    void decipher_oracle_answer() {
        std::ifstream answer(oracle_out_filename);
        std::string validity;
        answer >> validity;
        if (validity == "True") {
            int variable;
            int variables_num;
            answer >> variables_num;
            for (int i = 0; i < variables_num; i++) {
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
            for (int& variable : variables) {
                int family_id = variable_map[variable].second + 1;
                output << family_id << " ";
            }
        }
    }
};

#endif  // TASK2_H_
