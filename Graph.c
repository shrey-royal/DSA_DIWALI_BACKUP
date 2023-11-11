#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 100

//for list
struct Node {
    int vertex;
    struct Node* next;
};

void adjacencyMatrix(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void adjancencyList(struct Node* adjancencyList[], int vertices) {
    for (int i = 0; i < vertices; i++) {
        printf("Vertex %d: ", i);
        struct Node* current = adjancencyList[i];
        while (current != NULL) {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void addEdge(struct Node* adjancencyList[], int start, int end) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = end;

    newNode->next = adjancencyList[start];
    adjancencyList[start] = newNode;
}


int main() {
    int vertices, edges;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};
    struct Node* list[MAX_VERTICES] = {NULL};

    printf("\nEnter the number of vertices: ");
    scanf("%d", &vertices);

    printf("\nEnter the number of edges: ");
    scanf("%d", &edges);

    printf("\nEnter the edges (start vertex, end vertex): \n");
    for (int i = 0; i < edges; i++) {
        int start, end;
        scanf("%d %d", &start, &end);

        graph[start][end] = 1;
        graph[end][start] = 1;

        addEdge(list, start, end);
        addEdge(list, end, start);
    }

    printf("\nAdjancency Matrix: \n");
    adjacencyMatrix(graph, vertices);

    printf("\nAdjancency List: \n");
    adjancencyList(list, vertices);
    

    return 0;
}

/*
Enter the number of nodes in the graph: 4
Enter the edges in the graph (from to weight, -1 to stop):
0 1 5
1 2 3
2 3 7
3 0 2
-1 -1 -1

Graph Matrix:
0 5 0 2
5 0 3 0
0 3 0 7
2 0 7 0


*/