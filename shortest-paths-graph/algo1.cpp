#include <limits.h>

#include <queue>

#include "algo.h"

namespace std {

vector<int> shortest_path(const vector<vector<edge>>& graph, int src) {
    int V = graph.size();

    // Using priority_queue as min-heap
    priority_queue<edge, vector<edge>, greater<edge>> pq;

    vector<int> dist(V, INT_MAX);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        // The first vertex in the pair is the minimum distance
        // vertex, extract it from priority queue.
        int u = pq.top().second;
        pq.pop();

        // Get all adjacent nodes of u.
        for (auto x : graph[u]) {
            int v = x.first;
            int weight = x.second;

            // If there is a shorter path from u to v, update dist
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

vector<vector<int>> shortest_path_all(const vector<vector<edge>>& graph) {
    /* Implements Djikstra's algorithm using min-heap*/

    int V = graph.size();  // Number of vertices
    vector<vector<int>> dist_all(V, vector<int>(V));

    for (int vertex = 0; vertex < V; vertex++) {
        dist_all[vertex] = shortest_path(graph, vertex);
    }

    return dist_all;
}
}  // namespace std
