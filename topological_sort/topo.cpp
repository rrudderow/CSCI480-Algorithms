#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
    int vertices; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    // Helper function for DFS to detect cycles and perform topological sort
    bool dfs(int v, vector<bool>& visited, vector<bool>& recStack, stack<int>& topologicalOrder) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (int neighbor : adj[v]) {
                if (!visited[neighbor] && dfs(neighbor, visited, recStack, topologicalOrder)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true; // Cycle detected
                }
            }
        }
        recStack[v] = false; // Remove vertex from recursion stack
        topologicalOrder.push(v); // Push to topological order
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
        stack<int> topo;

        for (int i = 0; i < vertices; i++) {
            if (dfs(i, visited, recStack, topo))
                return false; // Cycle found
        }
        return true; // No cycles found, it's a DAG
    }

    // Topological Sort function
    vector<int> topologicalSort() {
        vector<bool> visited(vertices, false);
        vector<bool> recStack(vertices, false);
        stack<int> topologicalOrder;
        vector<int> result;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                if (dfs(i, visited, recStack, topologicalOrder)) {
                    throw runtime_error("Graph is not a DAG, cannot perform topological sort.");
                }
            }
        }

        // Transfer elements from stack to result vector
        while (!topologicalOrder.empty()) {
            result.push_back(topologicalOrder.top());
            topologicalOrder.pop();
        }

        return result;
    }
};

int main() {
    Graph g(1000); // Create a graph with 1000 vertices

    // Define a list of edges
    vector<pair<int, int>> edges;

    // Create edge pairs
    for (int i = 0; i < 1000; ++i) {
        if (i + 1 < 1000) edges.emplace_back(i, i + 1); // Connect i to i + 1
        if (i + 2 < 1000) edges.emplace_back(i, i + 2); // Connect i to i + 2
        if (i + 3 < 1000) edges.emplace_back(i, i + 3); // Connect i to i + 3
    }

    // Add edges to the graph
    g.addEdges(edges);
    //g.addEdge(3, 0);

    if (!g.isDAG()) {
        cout << "The graph contains a cycle." << endl;
        //return 1;
    } else {
        cout << "The graph is a Directed Acyclic Graph (DAG)." << endl;
    }

    // Perform topological sort
    try {
        vector<int> topoOrder = g.topologicalSort();
        cout << "Topological Sort Order: ";
        for (int vertex : topoOrder) {
            cout << vertex << " ";
        }
        cout << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
