#include <limits.h>

#include "algo.h"

namespace std {

vector<vector<int>> shortest_path_all(const vector<vector<edge>>& graph) {
    /* Implements Floyd-Warshall's algorithm */

    int V = graph.size();  // Number of vertices
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

    /* Convert adjacency list to adjacency matrix and initialize solution */
    for (int i = 0; i < V; i++) {
        for (auto j : graph[i]) {
            dist[i][j.first] = j.second;
        }
    }
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
    }

    /* Add all vertices one by one to the set of intermediate vertices. */
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}
}  // namespace std
