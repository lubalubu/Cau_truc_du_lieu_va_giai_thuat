#include <iostream>
using namespace std;

class Graph {
private:
    int numVertices;
    int** adjMatrix;
    char* vertices;

public:
    Graph(int n) {
        numVertices = n;
        adjMatrix = new int*[n];
        for (int i = 0; i < n; i++) {
            adjMatrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = 0;
            }
        }
        vertices = new char[n];
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        delete[] vertices;
    }

    void addVertex(int index, char name) {
        vertices[index] = name;
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
    }

    void BFS(int start) {
        bool* visited = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }

        int* queue = new int[numVertices];
        int front = 0, rear = 0;

        cout << "BFS: ";
        queue[rear++] = start;
        visited[start] = true;

        while (front != rear) {
            int current = queue[front++];
            cout << vertices[current] << " ";

            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = true;
                }
            }
        }
        cout << endl;

        delete[] visited;
        delete[] queue;
    }

    void DFS(int start) {
        bool* visited = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }

        int* stack = new int[numVertices];
        int top = -1;

        cout << "DFS: ";
        stack[++top] = start;

        while (top != -1) {
            int current = stack[top--];

            if (!visited[current]) {
                visited[current] = true;
                cout << vertices[current] << " ";
            }

            for (int i = numVertices - 1; i >= 0; i--) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
        cout << endl;

        delete[] visited;
        delete[] stack;
    }
};

int main() {
    // Initialize graph based on the given matrix
    int numVertices = 7;
    Graph g(numVertices);

    // Add vertices
    g.addVertex(0, 'a');
    g.addVertex(1, 'b');
    g.addVertex(2, 'c');
    g.addVertex(3, 'd');
    g.addVertex(4, 'e');
    g.addVertex(5, 'g');
    g.addVertex(6, 'h');

    // Add edges based on the adjacency list
    g.addEdge(0, 1); // a -> b
    g.addEdge(0, 3); // a -> d
    g.addEdge(0, 5); // a -> g
    g.addEdge(0, 6); // a -> h

    g.addEdge(1, 0); // b -> a
    g.addEdge(1, 2); // b -> c
    g.addEdge(1, 3); // b -> d
    g.addEdge(1, 4); // b -> e
    g.addEdge(1, 5); // b -> g
    g.addEdge(1, 6); // b -> h

    g.addEdge(2, 1); // c -> b
    g.addEdge(2, 3); // c -> d
    g.addEdge(2, 5); // c -> g
    g.addEdge(2, 6); // c -> h

    g.addEdge(3, 0); // d -> a
    g.addEdge(3, 1); // d -> b
    g.addEdge(3, 2); // d -> c
    g.addEdge(3, 4); // d -> e
    g.addEdge(3, 5); // d -> g
    g.addEdge(3, 6); // d -> h

    g.addEdge(4, 0); // e -> a
    g.addEdge(4, 1); // e -> b
    g.addEdge(4, 3); // e -> d
    g.addEdge(4, 5); // e -> g
    g.addEdge(4, 6); // e -> h

    g.addEdge(5, 0); // g -> a
    g.addEdge(5, 1); // g -> b
    g.addEdge(5, 2); // g -> c
    g.addEdge(5, 3); // g -> d
    g.addEdge(5, 4); // g -> e
    g.addEdge(5, 6); // g -> h

    g.addEdge(6, 0); // h -> a
    g.addEdge(6, 2); // h -> c
    g.addEdge(6, 3); // h -> d
    g.addEdge(6, 4); // h -> e
    g.addEdge(6, 5); // h -> g

    // Perform BFS and DFS starting from vertex 'a' (index 0)
    g.BFS(0);
    g.DFS(0);

    return 0;
}