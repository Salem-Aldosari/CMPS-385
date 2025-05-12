#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

// Definition of the Graph class
class Graph {
    int V;          // Number of vertices in the graph
    list<int>* adj; // Pointer to an array of adjacency lists

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int V);
    // Function to add an edge between two vertices
    void addEdge(int v, int w);
    // Function to perform Breadth-First Search starting from a given vertex
    void BFS(int start);
    // Function to perform Depth-First Search starting from a given vertex
    void DFS(int start);
};

// Implementation of the Graph constructor
Graph::Graph(int V) {
    this->V = V;          // Initialize the number of vertices
    adj = new list<int>[V]; // Create an array of adjacency lists, one for each vertex
}

// Implementation of the addEdge function
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add an edge from vertex v to vertex w (directed graph)
}

// Implementation of the Breadth-First Search (BFS) function
void Graph::BFS(int start) {
    vector<bool> visited(V, false); // Create a boolean vector to mark visited vertices, initially all false
    queue<int> q;                  // Create a queue for BFS

    visited[start] = true; // Mark the starting vertex as visited
    q.push(start);        // Enqueue the starting vertex

    while (!q.empty()) { // Continue as long as the queue is not empty
        int v = q.front(); // Dequeue a vertex from the front of the queue
        q.pop();          // Remove the front element
        cout << v << " ";  // Print the visited vertex

        // Iterate through the adjacency list of the dequeued vertex
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            // If the adjacent vertex has not been visited
            if (!visited[*i]) {
                visited[*i] = true; // Mark it as visited
                q.push(*i);        // Enqueue it
            }
        }
    }
}

// Implementation of the Depth-First Search (DFS) function
void Graph::DFS(int start) {
    vector<bool> visited(V, false); // Create a boolean vector to mark visited vertices, initially all false
    stack<int> s;                  // Create a stack for DFS

    visited[start] = true; // Mark the starting vertex as visited
    s.push(start);        // Push the starting vertex onto the stack
    cout << start << " "; // Print the starting vertex

    while (!s.empty()) { // Continue as long as the stack is not empty
        int v = s.top();    // Get the top vertex from the stack (without removing it)
        bool found = false; // Flag to check if an unvisited neighbor is found

        // Iterate through the adjacency list of the top vertex
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            // If an adjacent vertex has not been visited
            if (!visited[*i]) {
                visited[*i] = true; // Mark it as visited
                s.push(*i);        // Push it onto the stack
                cout << *i << " "; // Print the visited neighbor
                found = true;      // Set the flag to true
                break;            // Move to the newly pushed neighbor
            }
        }

        // If no unvisited neighbor is found, pop the current vertex from the stack
        if (!found) {
            s.pop();
        }
    }
}

// Main function where the program execution begins
int main() {
    // Create a Graph object with 7 vertices
    Graph g(7);
    // Add edges to the graph for the new example
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    // Perform Breadth-First Search starting from vertex 0 and print the traversal
    cout << "Breadth First Traversal (starting from 0):\n";
    g.BFS(0);

    cout << "\nDepth First Traversal (starting from 0):\n";
    g.DFS(0);

    return 0; // Indicate successful program execution
}