#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES];
int numNodes;

void addEdge(int from , int to, int weight) {
    graph[from][to] = weight;
    graph[to][from] = weight;   //assuming undirected graph
}

void initializeGraph() {
    printf("\nEnter the number of nodes in the graph: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the edges in the graph (from to weight, -1 to stop):\n");
    int from, to, weight;
    while(1) {
        scanf("%d %d %d", &from, &to, &weight);
        if(from == -1 || to == -1 || weight == -1) break;
        addEdge(from, to, weight);
    }
}

void dfsHelper(int node, int visited[]) {
    printf("%d ", node);
    visited[node] = 1;

    for (int i = 0; i < numNodes; i++) if(graph[node][i] != 0 && !visited[i]) dfsHelper(i, visited);
}

void depthFirstSearch(int startNode) {
    int visited[MAX_NODES] = {0};

    printf("Depth-First Search starting from node %d: ", startNode);
    dfsHelper(startNode, visited);
    printf("\n");
}

void breadthFirstSearch(int startNode) {
    int queue[MAX_NODES];
    int front = -1, rear = -1;
    int visited[MAX_NODES] = {0};

    printf("\nBreadth-First Search starting from node %d: ", startNode);
    
    visited[startNode] = 1;
    queue[++rear] = startNode;

    while(front != rear) {
        int currentNode = queue[++front];
        printf("%d ", currentNode);

        for (int i = 0; i < numNodes; i++) {
            if(graph[currentNode][i] != 0 && !visited[i]) {
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

    for (int i = 0; i < numNodes; i++) {
        distance[i] = INT_MAX;
    }

    distance[startNode] = 0;
    for (int count = 0; count < numNodes; count++) {
        int u = -1;
        for (int i = 0; i < numNodes; i++)
        {
            if(!visited[i] && (u == -1 || distance[i] < distance[u])) u = i;
        }
        visited[u] = 1;

        for (int v = 0; v < numNodes; v++) {
            if(graph[u][v] != 0 && !visited[v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) distance[v] = distance[u] = graph[u][v];
        }
    }

    printf("\nShortest distance from node %d using Dijsktra's Algorithm: \n", startNode);
    for (int i = 0; i < numNodes; i++) printf("\nNode %d: %d", i, distance[i]);
}


int main() {
    int choice, start;

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
                printf("\nEnter the starting node for DFS: ");
                scanf("%d", &start);
                depthFirstSearch(start);
                break;

            case 2:
                printf("\nEnter the starting node for bfs: ");
                scanf("%d", &start);
                breadthFirstSearch(start);
                break;

            case 3:
                printf("\nEnter the starting node for Dijkstra's Algorithm: ");
                scanf("%d", &start);
                dijkstra(start);
                break;

            case 7:
                printf("\nGoodBYE!");
                break;
            
            default:
                printf("\nInvalid Choice. Please Try Again.\n");
                break;
        }
    }while(choice != 7);
    return 0;
}

