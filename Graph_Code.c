#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES];
int numNodes;

// Function prototypes
void initializeGraph();
void addEdge(int from, int to, int weight);
void depthFirstSearch(int startNode);
void breadthFirstSearch(int startNode);
void dijkstra(int startNode);
void bellmanFord(int startNode);
void prim();
void kruskal();

int main() {
    int choice;

    initializeGraph();

    do {
        printf("\nGraph Operations Menu:\n");
        printf("1. Depth-First Search\n");
        printf("2. Breadth-First Search\n");
        printf("3. Dijkstra's Algorithm\n");
        printf("4. Bellman-Ford Algorithm\n");
        printf("5. Prim's Algorithm\n");
        printf("6. Kruskal's Algorithm\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the starting node for DFS: ");
                int dfsStart;
                scanf("%d", &dfsStart);
                depthFirstSearch(dfsStart);
                break;

            case 2:
                printf("Enter the starting node for BFS: ");
                int bfsStart;
                scanf("%d", &bfsStart);
                breadthFirstSearch(bfsStart);
                break;

            case 3:
                printf("Enter the starting node for Dijkstra's Algorithm: ");
                int dijkstraStart;
                scanf("%d", &dijkstraStart);
                dijkstra(dijkstraStart);
                break;

            case 4:
                printf("Enter the starting node for Bellman-Ford Algorithm: ");
                int bellmanFordStart;
                scanf("%d", &bellmanFordStart);
                bellmanFord(bellmanFordStart);
                break;

            case 5:
                prim();
                break;

            case 6:
                kruskal();
                break;

            case 7:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 7);

    return 0;
}

void initializeGraph() {
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &numNodes);

    // Initialize the graph matrix
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the edges in the graph (from to weight, -1 to stop):\n");
    int from, to, weight;
    while (1) {
        scanf("%d %d %d", &from, &to, &weight);
        if (from == -1 || to == -1 || weight == -1) {
            break;
        }
        addEdge(from, to, weight);
    }
}

void addEdge(int from, int to, int weight) {
    graph[from][to] = weight;
    graph[to][from] = weight;  // Assuming undirected graph
}

void depthFirstSearchUtil(int node, int visited[]) {
    printf("%d ", node);
    visited[node] = 1;

    for (int i = 0; i < numNodes; ++i) {
        if (graph[node][i] != 0 && !visited[i]) {
            depthFirstSearchUtil(i, visited);
        }
    }
}

void depthFirstSearch(int startNode) {
    int visited[MAX_NODES] = {0};

    printf("Depth-First Search starting from node %d: ", startNode);
    depthFirstSearchUtil(startNode, visited);
    printf("\n");
}

void breadthFirstSearch(int startNode) {
    int queue[MAX_NODES];
    int front = -1, rear = -1;
    int visited[MAX_NODES] = {0};

    printf("Breadth-First Search starting from node %d: ", startNode);

    visited[startNode] = 1;
    queue[++rear] = startNode;

    while (front != rear) {
        int currentNode = queue[++front];
        printf("%d ", currentNode);

        for (int i = 0; i < numNodes; ++i) {
            if (graph[currentNode][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }

    printf("\n");
}

void dijkstra(int startNode) {
    int distance[MAX_NODES];
    int visited[MAX_NODES] = {0};

    for (int i = 0; i < numNodes; ++i) {
        distance[i] = INT_MAX;
    }

    distance[startNode] = 0;

    for (int count = 0; count < numNodes - 1; ++count) {
        int u = -1;
        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i] && (u == -1 || distance[i] < distance[u])) {
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < numNodes; ++v) {
            if (graph[u][v] != 0 && !visited[v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    printf("Shortest distances from node %d using Dijkstra's Algorithm:\n", startNode);
    for (int i = 0; i < numNodes; ++i) {
        printf("Node %d: %d\n", i, distance[i]);
    }
}

void bellmanFord(int startNode) {
    int distance[MAX_NODES];

    for (int i = 0; i < numNodes; ++i) {
        distance[i] = INT_MAX;
    }

    distance[startNode] = 0;

    for (int count = 0; count < numNodes - 1; ++count) {
        for (int u = 0; u < numNodes; ++u) {
            for (int v = 0; v < numNodes; ++v) {
                if (graph[u][v] != 0 && distance[u] != INT_MAX &&
                    distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                }
            }
        }
    }

    printf("Shortest distances from node %d using Bellman-Ford Algorithm:\n", startNode);
    for (int i = 0; i < numNodes; ++i) {
        printf("Node %d: %d\n", i, distance[i]);
    }
}

void prim() {
    int parent[MAX_NODES];
    int key[MAX_NODES];
    int mstSet[MAX_NODES] = {0};

    for (int i = 0; i < numNodes; ++i) {
        key[i] = INT_MAX;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numNodes - 1; ++count) {
        int u = -1;
        for (int i = 0; i < numNodes; ++i) {
            if (!mstSet[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        mstSet[u] = 1;

        for (int v = 0; v < numNodes; ++v) {
            if (graph[u][v] != 0 && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Minimum Spanning Tree using Prim's Algorithm:\n");
    for (int i = 1; i < numNodes; ++i) {
        printf("Edge: %d - %d, Weight: %d\n", parent[i], i, graph[i][parent[i]]);
    }
}

void unionSets(int parent[], int i, int j) {
    int iParent = parent[i];
    int jParent = parent[j];

    parent[i] = jParent;
    for (int k = 0; k < numNodes; ++k) {
        if (parent[k] == iParent) {
            parent[k] = jParent;
        }
    }
}

int find(int parent[], int i) {
    return parent[i];
}

void kruskal() {
    int parent[MAX_NODES];
    int minEdge, u, v;

    // Initialize sets for each node
    for (int i = 0; i < numNodes; ++i) {
        parent[i] = i;
    }

    printf("Minimum Spanning Tree using Kruskal's Algorithm:\n");

    while (1) {
        minEdge = INT_MAX;
        u = -1;
        v = -1;

        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                if (find(parent, i) != find(parent, j) && graph[i][j] != 0 && graph[i][j] < minEdge) {
                    minEdge = graph[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        if (u == -1 || v == -1) {
            break; // No more edges to consider
        }

        unionSets(parent, u, v);

        printf("Edge: %d - %d, Weight: %d\n", u, v, minEdge);
    }
}


/*
Sample test Case:

Number of nodes in the graph: 5
Enter the edges in the graph (from to weight, -1 to stop):
0 1 2
0 2 4
1 2 1
1 3 7
2 3 3
3 4 1
-1 -1 -1

*/