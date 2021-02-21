#ifndef ALGO_H
#define ALGO_H

#include <vector>

namespace std {
/*
 * edge.first  -> the idx of the neighbour
 * edge.second -> the cost
 */
typedef pair<int, int> edge;

/**
 * For a given input graph T, computes the distance from src node to every other
 * node in the graph.
 *
 * @param graph: The graph is represented using adjacency lists (graph[i] -
 * gives you the neighbours of node i)
 * @param src: The source node
 * @returns: The vector with the minimum distances between node src and all the
 * other nodes. If there is no way to reach node j from i, store INT_MAX in the
 * matrix (print it as "inf" in the tests)
 */
vector<int> shortest_path(const vector<vector<edge>>& graph, int src);

/**
 * For a given input graph T, computes the distance from every node to every
 * other node in the graph.
 *
 * @param graph: The graph is represented using adjacency lists (graph[i] -
 * gives you the neighbours of node i)
 * @returns: The adjacency matrix with the minimum distances between every node.
 * If there is no way to reach node j from i, store INT_MAX in the matrix
 * (print it as "inf" in the tests)
 */
vector<vector<int>> shortest_path_all(const vector<vector<edge>>& graph);
}  // namespace std

#endif
