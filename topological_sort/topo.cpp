#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

class Graph {
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

    // Topological Sort function
    vector<int> topoSortGraph() {
        vector<bool> visited(vertices, false);
        vector<bool> recStack(vertices, false);
        stack<int> topologicalOrder;
        vector<int> result;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                if (dfs(i, visited, recStack, topologicalOrder)) {
                    throw runtime_error("Cannot perform topological sort - not a DAG.");
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
    vector<string> topoSortTasks(unordered_map<int, string> tasks) {
        vector<bool> visited(vertices, false);
        vector<bool> recStack(vertices, false);
        stack<int> topologicalOrder;
        vector<string> resultTasks;

        for (auto i : tasks) {
            if (!visited[i.first]) {
                if (dfs(i.first, visited, recStack, topologicalOrder)) {
                    throw runtime_error("Cannot perform topological sort - not a DAG.");
                }
            }
        }

        // Transfer elements from stack to result vector
        while (!topologicalOrder.empty()) {
            resultTasks.push_back(tasks[topologicalOrder.top()]);
            topologicalOrder.pop();
        }

        return resultTasks;
    }
    void printTopo(vector<int> topoOrder){
        cout << "Topological Sort Order: ";
        for (int vertex : topoOrder) {
            cout << vertex << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph g(10000);

    vector<pair<int, int>> edges;

    for (int i = 0; i < 10000; ++i) {
        if (i + 1 < 10000) edges.emplace_back(i, i + 1); // Connect i to i + 1
        if (i + 2 < 10000) edges.emplace_back(i, i + 2); // Connect i to i + 2
        if (i + 3 < 10000) edges.emplace_back(i, i + 3); // Connect i to i + 3
    }

    g.addEdges(edges);

    // To make a cycle:
    //g.addEdge(1, 0);

    try {
        vector<int> topoOrder = g.topoSortGraph();
        cout << "Topological Sort has finished\n";
        //g.printTopo(topoOrder);
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Run topological sort on Graph of tasks

    unordered_map<int, string> tasks;

    // unordered_map of classes
    tasks[0] = "Class 0";
    tasks[1] = "Class 1";
    tasks[2] = "Class 2";
    tasks[3] = "Class 3";
    tasks[4] = "Class 4";
    tasks[5] = "Class 5";
    tasks[6] = "Class 6";

    Graph t(7);

    // Add edges to represent class prerequisites
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(0, 5);
    t.addEdge(1, 4);
    t.addEdge(3, 4);
    t.addEdge(3, 5);
    t.addEdge(3, 6);
    t.addEdge(3, 2);
    t.addEdge(5, 2);
    t.addEdge(6, 0);
    t.addEdge(6, 4);

    //t.addEdge(1, 0);

    try {
        vector<string> taskOrder = t.topoSortTasks(tasks);
        cout << "Topological Sort has finished\n";
        for(auto str : taskOrder){
            cout << str << endl;
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
