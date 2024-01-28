#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // Adjust this based on your graph size

int visited[MAX_VERTICES];
int bfsOrder[MAX_VERTICES];
int front = -1, rear = -1;

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjacencyList;
} Graph;

// Function to create a new graph with 'n' vertices
Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = n;
    graph->adjacencyList = (Node**)malloc(n * sizeof(Node*));

    for (int i = 0; i < n; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Function to enqueue a vertex in the BFS queue
void enqueue(int vertex) {
    if (rear == MAX_VERTICES - 1) {
        printf("Queue is full.\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    bfsOrder[rear] = vertex;
}

// Function to dequeue a vertex from the BFS queue
int dequeue() {
    if (front == -1) {
        printf("Queue is empty.\n");
        return -1;
    }
    int vertex = bfsOrder[front];
    front++;
    if (front > rear) {
        front = rear = -1;
    }
    return vertex;
}

// Breadth-First Search function
void bfs(Graph* graph, int startVertex) {
    enqueue(startVertex);
    visited[startVertex] = 1;

    while (front != -1) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        Node* currentNode = graph->adjacencyList[currentVertex];
        while (currentNode != NULL) {
            int adjacentVertex = currentNode->vertex;
            if (!visited[adjacentVertex]) {
                enqueue(adjacentVertex);
                visited[adjacentVertex] = 1;
            }
            currentNode = currentNode->next;
        }
    }
}

int main() {
    int numVertices = 6; // Change this based on your graph size
    Graph* graph = createGraph(numVertices);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);

    // Initialize visited array
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    // Perform BFS from the first vertex
    printf("BFS Order: ");
    bfs(graph, 0);
    printf("\n");

    return 0;
}
