

#11 employee

#include<stdio.h>
#include<stdlib.h>

typedef struct Employee
{
    int emp_id;
    struct Employee* left;
    struct Employee* right;
}Employee;

Employee* createEmployee(int emp_id)
{
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if(newEmployee == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
    newEmployee->emp_id = emp_id;
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

Employee* insertEmployee(Employee* root, int emp_id)
{
    if(root == NULL)
        return createEmployee(emp_id);
    if(emp_id < root->emp_id)
        root->left = insertEmployee(root->left, emp_id);
    else if(emp_id > root->emp_id)
        root->right = insertEmployee(root->right, emp_id);

    return root;
}

Employee* searchEmployee(Employee* root, int emp_id)
{
    if(root == NULL || root->emp_id == emp_id)
        return root;

    if(emp_id < root->emp_id)
        return searchEmployee(root->left, emp_id);
    else
        return searchEmployee(root->right, emp_id);
}

void inOrder(Employee* root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("Employee Id: %d\n",root->emp_id);
        inOrder(root->right);
    }
}

void freeBST(Employee* root)
{
    if(root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main()
{
    Employee* root = NULL;
    int num_employees, emp_id;

    printf("Enter the number of employees: ");
    scanf("%d", &num_employees);

    printf("Enter the employee IDs:\n");
    for(int i = 0; i < num_employees; i++)
    {
        scanf("%d", &emp_id);
        root = insertEmployee(root, emp_id);
    }

    int search_id;
    printf("Enter the employee ID to search: ");
    scanf("%d", &search_id);

    Employee* result = searchEmployee(root, search_id);
    if(result != NULL)
        printf("Employee ID %d found\n", search_id);
    else
        printf("Employee ID %d not found\n", search_id);

    printf("Employees records sorted by id: \n");
    inOrder(root);

    freeBST(root);

    return 0;
}



#12 & #13

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
    int isThreaded;
};

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

struct Node *inorderSuccessor(struct Node *node) {
    if (node == NULL)
        return NULL;
    struct Node *temp = node->right;
    if (node->isThreaded == 1) {
        while (temp != NULL && temp->left != NULL)
            temp = temp->left;
    }
    return temp;
}

void createThreaded(struct Node *root, struct Node **prev) {
    if (root == NULL)
        return;
    createThreaded(root->left, prev);
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1;
    }
    *prev = root;
    if (root->right == NULL) {
        createThreaded(root->right, prev);
    }
}

void inorderTraversal(struct Node *root) {
    struct Node *current = root;
    while (current != NULL) {
        while (current->left != NULL)
            current = current->left;
        printf("%d ", current->data);
        current = inorderSuccessor(current);
    }
}

void preorderTraversal(struct Node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    if (root->isThreaded != 1)
        preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    struct Node *root = NULL;
    int num_nodes;
    printf("Enter the number of nodes in the binary tree: ");
    scanf("%d", &num_nodes);

    printf("Enter the elements of the binary tree:\n");
    for (int i = 0; i < num_nodes; ++i) {
        int data;
        scanf("%d", &data);
        if (root == NULL) {
            root = createNode(data);
        } else {
            struct Node *temp = root;
            struct Node *parent = NULL;
            while (temp != NULL) {
                parent = temp;
                if (data < temp->data)
                    temp = temp->left;
                else
                    temp = temp->right;
            }
            if (data < parent->data)
                parent->left = createNode(data);
            else
                parent->right = createNode(data);
        }
    }

    struct Node *prev = NULL;
    createThreaded(root, &prev);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}




#14 & #15

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node *newNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node *insert(struct Node *node, int key) {
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->left) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->left) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

int main() {
    struct Node *root = NULL;

    int num_nodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);

    printf("Enter the keys:\n");
    for (int i = 0; i < num_nodes; ++i) {
        int key;
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Inorder Traversal: ");
    inOrder(root);
    printf("\n");

    printf("Enter the key to delete: ");
    int key_to_delete;
    scanf("%d", &key_to_delete);
    root = deleteNode(root, key_to_delete);

    printf("Inorder Traversal after deletion: ");
    inOrder(root);
    printf("\n");

    return 0;
}



#16 Adjacency Matrix
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int numVertices;
    int** adjMatrix;
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // If undirected graph
}

void displayAdjMatrix(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        for (int j = 0; j < graph->numVertices; ++j) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    printf("Breadth-First Search Traversal: ");
    queue[rear++] = startVertex;
    visited[startVertex] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < graph->numVertices; ++i) {
            if (graph->adjMatrix[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int top = -1;

    printf("Depth-First Search Traversal: ");
    stack[++top] = startVertex;
    visited[startVertex] = 1;

    while (top != -1) {
        int current = stack[top--];
        printf("%d ", current);

        for (int i = 0; i < graph->numVertices; ++i) {
            if (graph->adjMatrix[current][i] && !visited[i]) {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(visited);
    free(stack);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the edges (source and destination vertices) in the graph:\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    displayAdjMatrix(graph);

    int startVertex;
    printf("Enter the starting vertex for BFS and DFS traversals: ");
    scanf("%d", &startVertex);

    BFS(graph, startVertex);
    DFS(graph, startVertex);

    // Free allocated memory
    for (int i = 0; i < numVertices; ++i) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
Enter the number of vertices in the graph: 5
Enter the number of edges in the graph: 6
Enter the edges (source and destination vertices) in the graph:
0 1
0 2
1 2
1 3
2 3
3 4
Enter the starting vertex for BFS and DFS traversals: 0



#17 Adjancency list

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adj;
};

struct Graph* createGraph(int V) {
    struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
    G->V = V;
    G->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; ++i) {
        G->adj[i] = NULL;
    }
    return G;
}

void addEdge(struct Graph* G, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = G->adj[src];
    G->adj[src] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = G->adj[dest];
    G->adj[dest] = newNode;
}

void displayAdjList(struct Graph* G) {
    printf("Adjacency List:\n");
    for (int i = 0; i < G->V; ++i) {
        printf("%d -> ", i);
        struct Node* temp = G->adj[i];
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void BFS(struct Graph* G, int startVertex) {
    int* visited = (int*)calloc(G->V, sizeof(int));
    int* queue = (int*)malloc(G->V * sizeof(int));
    int f = 0, r = 0;

    printf("BFS Traversal: ");
    queue[r++] = startVertex;
    visited[startVertex] = 1;

    while (f < r) {
        int current = queue[f++];
        printf("%d ", current);

        struct Node* temp = G->adj[current];
        while (temp) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {
                queue[r++] = neighbor;
                visited[neighbor] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

void DFSUtil(struct Graph* G, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = G->adj[vertex];
    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            DFSUtil(G, neighbor, visited);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* G, int startVertex) {
    int* visited = (int*)calloc(G->V, sizeof(int));
    printf("DFS Traversal: ");
    DFSUtil(G, startVertex, visited);
    printf("\n");
    free(visited);
}

int main() {
    int V, E;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    struct Graph* G = createGraph(V);

    printf("Enter the edges (source and destination vertices) in the graph:\n");
    for (int i = 0; i < E; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(G, src, dest);
    }

    displayAdjList(G);

    int startVertex;
    printf("Enter the starting vertex for BFS and DFS traversals: ");
    scanf("%d", &startVertex);

    BFS(G, startVertex);
    DFS(G, startVertex);

    // Free allocated memory
    for (int i = 0; i < V; ++i) {
        struct Node* temp = G->adj[i];
        while (temp) {
            struct Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(G->adj);
    free(G);

    return 0;
}
Enter the number of vertices in the graph: 5
Enter the number of edges in the graph: 6
Enter the edges (source and destination vertices) in the graph:
0 1
0 2
1 2
1 3
2 3
3 4
Enter the starting vertex for BFS and DFS traversals: 0


#18 prism algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with minimum key value
int minKey(int key[], bool mstSet[], int vertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the constructed MST stored in parent[]
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to implement Prim's algorithm to find MST of a graph
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[vertices]; // Array to store constructed MST
    int key[vertices];    // Key values used to pick minimum weight edge in cut
    bool mstSet[vertices]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 0th vertex in MST.
    key[0] = 0; // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, vertices);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < vertices; v++) {
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, vertices);
}

int main() {
    int vertices, edges;
    int graph[MAX_VERTICES][MAX_VERTICES];

    // Accept number of vertices and edges from user
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Initialize graph with all 0s
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }

    // Accept edges from user and their weights
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        graph[source][destination] = weight;
        graph[destination][source] = weight; // For undirected graph
    }

    // Print the Minimum Spanning Tree (MST) using Prim's algorithm
    printf("Minimum Spanning Tree using Prim's algorithm:\n");
    primMST(graph, vertices);

    return 0;
}

Enter the number of vertices: 4
Enter the number of edges: 5
Enter edges (source destination weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4



#19 Merge sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of students
#define MAX_STUDENTS 50

// Structure to represent a Student
struct StudentInfo {
    char name[50];
    int rollNo;
    int marks;
};

// Function to merge two subarrays arr[l..m] and arr[m+1..r]
// and count the number of swaps performed
void mergeStudents(struct StudentInfo students[], int l, int m, int r, int *swaps) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct StudentInfo left[n1], right[n2];

    // Copy data to temporary arrays left[] and right[]
    for (int i = 0; i < n1; i++)
        left[i] = students[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = students[m + 1 + j];

    // Merge the temporary arrays back into students[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i].rollNo <= right[j].rollNo) {
            students[k] = left[i];
            i++;
        } else {
            students[k] = right[j];
            j++;
            // Count the number of swaps performed
            *swaps += n1 - i;
        }
        k++;
    }

    // Copy the remaining elements of left[], if any
    while (i < n1) {
        students[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right[], if any
    while (j < n2) {
        students[k] = right[j];
        j++;
        k++;
    }
}

// Main function to implement merge sort on the student array
void sortStudents(struct StudentInfo students[], int l, int r, int *swaps) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sortStudents(students, l, m, swaps);
        sortStudents(students, m + 1, r, swaps);

        // Merge the sorted halves
        mergeStudents(students, l, m, r, swaps);
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Validate the number of students
    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number of students. Please enter a number between 1 and %d.\n", MAX_STUDENTS);
        return 1;
    }

    struct StudentInfo *students = (struct StudentInfo *)malloc(n * sizeof(struct StudentInfo));

    // Accept student details from the user
    printf("Enter student details:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Roll No.: ");
        scanf("%d", &students[i].rollNo);
        printf("Total Marks: ");
        scanf("%d", &students[i].marks);
    }

    // Perform merge sort on the student array based on rollNo
    int swaps = 0;
    sortStudents(students, 0, n - 1, &swaps);

    // Display the sorted array
    printf("\nSorted student details based on roll number:\n");
    printf("Name\tRoll No.\tTotal Marks\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\n", students[i].name, students[i].rollNo, students[i].marks);
    }

    // Display the number of swaps performed
    printf("\nNumber of swaps performed: %d\n", swaps);

    free(students);
    return 0;
}
 input name roll no marks in any order
