#include <limits.h>

#include <queue>

#include "algo.h"

namespace std {
vector<int> dijkstra(const vector<vector<edge>>& graph, int src) {
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

/**
 * Modified Bellman-Ford algorithm to reweight graph
 *
 * @param graph: initial graph
 * @returns the modified weights
 */
vector<int> bellman(const vector<vector<edge>>& graph) {
    int V = graph.size();

    queue<int> q;
    bool inq[V + 1] = {false};  // inq[i] stores whether node i is in queue

    vector<int> dist(V + 1, INT_MAX);

    // Create new vertex for reweighting
    vector<vector<edge>> modified_graph = graph;
    modified_graph.resize(V + 1);
    for (int i = 0; i < V; i++) {
        modified_graph[V].push_back(make_pair(i, 0));
    }

    // Push new vertex element to queue
    inq[V] = true;
    q.push(V);
    dist[V] = 0;

    while (!q.empty()) {
        int t = q.front();
        int E = modified_graph[t].size();
        q.pop();
        inq[t] = false;
        // Traverse all the outgoing edges
        for (int i = 0; i < E; i++) {
            int tn = modified_graph[t][i].first;
            // If there is room for relaxation
            if (dist[tn] > dist[t] + modified_graph[t][i].second) {
                dist[tn] = dist[t] + modified_graph[t][i].second;

                // If the node relaxed is not in the queue, add it to the queue.
                if (!inq[tn]) {
                    inq[tn] = true;
                    q.push(tn);
                }
            }
        }
    }

    // Remove the last added vertex
    dist.pop_back();

    return dist;
}
vector<vector<int>> shortest_path_all(const vector<vector<edge>>& graph) {
    /* Implements Johnson's algorithm */

    int V = graph.size();  // number of vertices

    // Call Bellman-Ford's algorithm to get modified weights
    vector<int> modify_weights = bellman(graph);

    // Update graph with modified weights
    vector<vector<edge>> modified_graph = graph;

    for (int u = 0; u < V; u++) {
        int E = graph[u].size();  // number of edges for each vertice
        for (int i = 0; i < E; i++) {
            int v = modified_graph[u][i].first;
            modified_graph[u][i].second += modify_weights[u];
            modified_graph[u][i].second -= modify_weights[v];
        }
    }

    // Run Dijkstra's algorithm on the reweighted graph
    vector<vector<int>> dist_all(V, vector<int>(V));

    for (int vertex = 0; vertex < V; vertex++) {
        dist_all[vertex] = dijkstra(modified_graph, vertex);
    }

    // Restore initial weights
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist_all[i][j] != INT_MAX) {
                dist_all[i][j] -= modify_weights[i];
                dist_all[i][j] += modify_weights[j];
            }
        }
    }

    return dist_all;
}
}  // namespace std
