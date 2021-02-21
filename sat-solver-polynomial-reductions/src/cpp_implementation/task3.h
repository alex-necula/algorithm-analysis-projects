// Copyright 2020
// Authors: Radu Nichita, Matei Simtinică

#ifndef TASK3_H_
#define TASK3_H_

#include "task.h"
#include "task1.h"
#include "task2.h"

/*
 * Task3
 * This being an optimization problem, the solve method's logic has to work differently.
 * You have to search for the minimum number of arrests by successively querying the oracle.
 * Hint: it might be easier to reduce the current task to a previously solved task
 */
class Task3 : public Task {
   private:
    std::string task2_in_filename;
    std::string task2_out_filename;
    int relationships_num;
    int families_num;
    std::vector<std::vector<int>> relationships;  // Adjacency matrix
    bool found_extended_family;
    std::vector<int> non_extended_family_ids;

   public:
    void solve() override {
        task2_in_filename = in_filename + "_t2";
        task2_out_filename = out_filename + "_t2";
        Task2 task2_solver = Task2();
        task2_solver.add_files(task2_in_filename, oracle_in_filename, oracle_out_filename,
                               task2_out_filename);
        read_problem_data();

        // Find minimum vertex-cover in family graph
        for (int k = 1; k <= families_num; k++) {
            reduce_to_task2(k);
            task2_solver.solve();
            extract_answer_from_task2(k);
            if (found_extended_family) break;
        }

        write_answer();
    }

    void read_problem_data() override {
        std::ifstream input(in_filename);

        input >> families_num >> relationships_num;

        // Initialize adjacency matrix
        relationships.resize(families_num, std::vector<int>(families_num));

        for (int i = 0; i < relationships_num; i++) {
            int a, b;
            input >> a >> b;
            relationships[a - 1][b - 1] = 1;
            relationships[b - 1][a - 1] = 1;
        }
    }

    void reduce_to_task2(int family_size) {
        std::ofstream input_task2(task2_in_filename);

        // Reducing Vertex-Cover to K-Clique

        int non_relationships_num = families_num * (families_num - 1) / 2 - relationships_num;
        input_task2 << families_num << " " << non_relationships_num << " "
                    << families_num - family_size << std::endl;

        for (int i = 0; i < families_num - 1; i++) {
            for (int j = i + 1; j < families_num; j++) {
                if (relationships[i][j] == 0) {
                    input_task2 << i + 1 << " " << j + 1 << std::endl;
                }
            }
        }
    }

    void extract_answer_from_task2(int family_size) {
        std::ifstream output_task2(task2_out_filename);

        std::string found;
        output_task2 >> found;
        if (found == "True") {
            found_extended_family = true;
            for (int i = 0; i < families_num - family_size; i++) {
                int a;
                output_task2 >> a;
                non_extended_family_ids.push_back(a);
            }
        } else {
            found_extended_family = false;
        }
    }

    void write_answer() override {
        std::ofstream output(out_filename);
        std::map<int,int> extended_family_map;

        for (int i = 1; i <= families_num; i++) {
            extended_family_map[i] = 1;
        }

        for (int& family_id : non_extended_family_ids) {
            extended_family_map[family_id] = 0;
        }

        for (auto& [key, value] : extended_family_map) {
            if (value == 1) {
                output << key << " ";
            }
        }
    };
};

#endif  // TASK3_H_
