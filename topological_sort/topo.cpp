#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
    int vertices; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    // Helper function for DFS to detect cycles
    bool dfs(int v, vector<bool>& visited, vector<bool>& recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (int neighbor : adj[v]) {
                if (!visited[neighbor] && dfs(neighbor, visited, recStack)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true; // Cycle detected
                }
            }
        }
        recStack[v] = false; // Remove vertex from recursion stack
        return false;
    }

public:
    Graph(int v) : vertices(v) {
        adj.resize(v);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void addEdges(const vector<pair<int, int>>& edges) {
        for (const auto& edge : edges) {
            addEdge(edge.first, edge.second);
        }
    }

    bool isDAG() {
        vector<bool> visited(vertices, false);
        vector<bool> recStack(vertices, false);

        for (int i = 0; i < vertices; i++) {
            if (dfs(i, visited, recStack)) {
                return false; // Cycle found
            }
        }
        return true; // No cycles found, it's a DAG
    }
};

int main() {
    /*
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    */
    Graph g(10000); // Create a graph with 10,000 vertices

    // Define a list of edges
    vector<pair<int, int>> edges;

    //Create 10,000 edge pairs
    for (int i = 0; i < 10000; ++i) {
        if (i + 1 < 1000) edges.emplace_back(i, i + 1); // Connect i to i + 1
        if (i + 2 < 1000) edges.emplace_back(i, i + 2); // Connect i to i + 2
        if (i + 3 < 1000) edges.emplace_back(i, i + 3); // Connect i to i + 3
    }

    // Add edges to the graph
    g.addEdges(edges);
    //g.addEdge(3, 0);

    if (!g.isDAG()) {
        cout << "The graph contains a cycle." << endl;
        return 0;
    } else {
        cout << "The graph is a Directed Acyclic Graph (DAG)." << endl;
    }

    return 0;
}
