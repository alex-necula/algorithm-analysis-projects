
#include <limits.h>

#include <queue>

#include "algo.h"

namespace std {

vector<int> shortest_path(const vector<vector<edge>>& graph, int src) {
    int V = graph.size();

    queue<int> q;
    bool inq[V] = {false};  // inq[i] stores whether node i is in queue

    vector<int> dist(V, INT_MAX);

    // Push source element to queue
    inq[src] = true;
    q.push(src);
    dist[src] = 0;

    while (!q.empty()) {
        int t = q.front();
        int E = graph[t].size();
        q.pop();
        inq[t] = false;
        // Traverse all the outgoing edges
        for (int i = 0; i < E; i++) {
            int tn = graph[t][i].first;
            // If there is room for relaxation
            if (dist[tn] > dist[t] + graph[t][i].second) {
                dist[tn] = dist[t] + graph[t][i].second;

                // If the node relaxed is not in the queue, add it to the queue.
                if (!inq[tn]) {
                    inq[tn] = true;
                    q.push(tn);
                }
            }
        }
    }

    return dist;
}

vector<vector<int>> shortest_path_all(const vector<vector<edge>>& graph) {
    /* Implements Bellman-Ford's algorithm using queue*/

    int V = graph.size();  // Number of vertices
    vector<vector<int>> dist_all(V, vector<int>(V));

    for (int vertex = 0; vertex < V; vertex++) {
        dist_all[vertex] = shortest_path(graph, vertex);
    }

    return dist_all;
}
}  // namespace std
