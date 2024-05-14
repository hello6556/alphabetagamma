

#22 inToPost

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 100

char stack[MAX];
char infix[MAX], postfix[MAX];
int top = -1;

void inToPost();
int space(char c);
int precedence(char symbol);
void print();
void push(char c);
char pop();
int isEmpty();

int main()
{
    printf("Enter the infix expression: ");
    gets(infix);
    inToPost();
    print();
    return 0;
}

void inToPost(){
    int i, j = 0;
    char symbol;
    char next;
    for (i = 0; i < strlen(infix); i++){
        symbol = infix[i];
        if (!space(symbol))
        {
            switch (symbol){
                case '(':
                    push(symbol);
                    break;
                case ')':
                    while ((next = pop()) != '(')
                        postfix[j++] = next;
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                case '^':
                    while (!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                        postfix[j++] = pop();
                    push(symbol);
                    break;
                default:
                    postfix[j++] = symbol;
            }
        }
    }
    while (!isEmpty())
        postfix[j++] = pop();
    postfix[j] = '\0';
}

int space(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    else
        return 0;
}

int precedence(char symbol)
{
    switch (symbol)
    {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void print()
{
    int i = 0;
    printf("The Equivalent postfix expression is: ");
    while (postfix[i]){
        printf("%c", postfix[i++]);
    }
    printf("\n");
}

void push(char c)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = c;
}

char pop()
{
    char c;
    if (top == -1)
    {
        printf("Stack underflow");
        exit(1);
    }
    c = stack[top];
    top = top - 1;
    return c;
}

int isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}



#23 Singly LL

#include<stdio.h>
#include<stdlib.h>

struct Node
{
    /* data */
    int data;
    struct Node* next;
};

struct Node* newNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Stack
{
    struct Node* top;
};

void initStack(struct Stack* stack)
{
    stack->top = NULL;
}

int isEmpty(struct Stack* stack)
{
    return (stack->top == NULL);
}

void push(struct Stack* stack, int data)
{
    struct Node* node = newNode(data);
    node->next = stack->top;
    stack->top = node;
    printf("%d pushed to stack\n", data);
}

int pop(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        printf("Stack is Empty\n");
        return -1;
    }
    struct Node* current = stack->top;
    int popped = current->data;
    stack->top = current->next;
    free(current);
    return popped;
}

void displayStack(struct Stack* stack)
{
    struct Node* current = stack->top;
    printf("Stack: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    struct Stack stack;
    initStack(&stack);

    int choice;
    int element;
    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to push onto the stack: ");
                scanf("%d", &element);
                push(&stack, element);
                break;
            case 2:
                element = pop(&stack);
                if (element != -1) {
                    printf("Popped element: %d\n", element);
                }
                break;
            case 3:
                displayStack(&stack);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}



#24 factorial and fibonacci

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

struct Stack
{
    int top;
    unsigned int capacity;
    int* array;
};

struct Stack* createStack(unsigned int capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
    if(isFull(stack))
    {
        printf("Stack Overflow");
        exit(1);
    }
    return stack->array[++stack->top]=item;
}

int pop(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        printf("Stack Underflow");
        return -1;
    }
    return stack->array[stack->top--];
}

void fibonacci(int n)
{
    struct Stack* stack = createStack(MAX_SIZE);

    push(stack, 0);
    push(stack, 1);
    printf("Fibonacci Series upto %d: \n",n);
    while (n > 0)
    {
        int a = pop(stack);
        printf("%d ",a);
        int b = pop(stack);
        push(stack,a);
        push(stack,a+b);
        n--;
    }
    printf("\n");
    free(stack->array);
    free(stack);
}

int factorial(int n)
{
    struct Stack* stack = createStack(MAX_SIZE);
    while (n > 0)
    {
        push(stack, n);
        n--;
    }
    int current = 1;
    while (!isEmpty(stack))
    {
        current *= pop(stack);
    }
    free(stack->array);
    free(stack);
    return current;
}

int main()
{
    int choice, n;
    printf("Choose an operation:\n");
    printf("1. Fibonacci Series\n");
    printf("2. Factorial\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the number of terms for Fibonacci Series: ");
            scanf("%d", &n);
            fibonacci(n);
            break;
        case 2:
            printf("Enter a number: ");
            scanf("%d", &n);
            printf("Factorial of %d is: %d\n", n, factorial(n));
            break;
        default:
            printf("Invalid choice! Please enter 1 or 2.\n");
    }

    return 0;
}



#25 Queue Operation

#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Queue
{
    struct Node* rear;
    struct Node* front;
};

struct Node* newNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initQueue(struct Queue* queue)
{
    queue->front = queue->rear = NULL;
}

int isEmpty(struct Queue* queue)
{
    return queue->front == NULL;
}

void enqueue(struct Queue* queue, int data)
{
    struct Node* node = newNode(data);
    if(isEmpty(queue))
        queue->front = queue->rear = node;
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
        
    printf("%d enqueued into the queue\n",data);
}

int dequeue(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        printf("Queue is Empty");
        exit(1);
    }
    struct Node* temp = queue->front;
    int dequeued = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return dequeued;
}

void displayQueue(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        printf("Queue is empty!\n");
        return;
    } 
    struct Node* current = queue->front;
    printf("Queue: ");
    while (current != NULL)
    {
        printf("%d ",current->data);
        current = current->next;
    }
    printf("\n");
}

void displayFront(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Front element: %d\n", queue->front->data);
}

void displayRear(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Rear element: %d\n", queue->rear->data);
}

int main()
{
    struct Queue queue;
    initQueue(&queue);

    int choice, data;

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Display Front Element\n");
        printf("5. Display Rear Element\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &data);
                enqueue(&queue, data);
                break;
            case 2:
                printf("Dequeued element: %d\n", dequeue(&queue));
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                displayFront(&queue);
                break;
            case 5:
                displayRear(&queue);
                break;
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while(choice != 6);

    return 0;
}



#26 circular queue

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5 // Maximum size of the circular queue

// Structure to represent a circular queue
struct CircularQueue {
    int* arr;
    int front, rear, size;
    unsigned cap;
};

// Function to create an empty circular queue
struct CircularQueue* createCircularQueue(unsigned cap) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->cap = cap;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1; // -1 indicates an empty queue
    queue->arr = (int*)malloc(queue->cap * sizeof(int));
    return queue;
}

// Function to check if the circular queue is empty
bool isEmpty(struct CircularQueue* queue) {
    return queue->size == 0;
}

// Function to check if the circular queue is full
bool isFull(struct CircularQueue* queue) {
    return queue->size == queue->cap;
}

// Function to add an element to the rear end of the circular queue
void enqueueRear(struct CircularQueue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->cap; // Circular increment
    queue->arr[queue->rear] = item;
    queue->size++;
    printf("%d enqueued to rear end of the queue.\n", item);
}

// Function to add an element to the front end of the circular queue
void enqueueFront(struct CircularQueue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->front = (queue->front - 1 + queue->cap) % queue->cap; // Circular decrement
    queue->arr[queue->front] = item;
    queue->size++;
    printf("%d enqueued to front end of the queue.\n", item);
}

// Function to remove an element from the rear end of the circular queue
int dequeueRear(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return -1 indicating queue underflow
    }
    int item = queue->arr[queue->rear];
    queue->rear = (queue->rear - 1 + queue->cap) % queue->cap; // Circular decrement
    queue->size--;
    return item;
}

// Function to remove an element from the front end of the circular queue
int dequeueFront(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return -1 indicating queue underflow
    }
    int item = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->cap; // Circular increment
    queue->size--;
    return item;
}

// Function to display the circular queue
void displayQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Circular Queue: ");
    int i;
    for (i = queue->front; i != queue->rear; i = (i + 1) % queue->cap)
        printf("%d ", queue->arr[i]);
    printf("%d\n", queue->arr[i]);
}

int main() {
    int choice, item;
    struct CircularQueue* queue = createCircularQueue(MAX_SIZE);

    while (1) {
        printf("\nCircular Queue Operations:\n");
        printf("1. Enqueue to rear\n");
        printf("2. Enqueue to front\n");
        printf("3. Dequeue from rear\n");
        printf("4. Dequeue from front\n");
        printf("5. Display the queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue to rear: ");
                scanf("%d", &item);
                enqueueRear(queue, item);
                break;
            case 2:
                printf("Enter the element to enqueue to front: ");
                scanf("%d", &item);
                enqueueFront(queue, item);
                break;
            case 3:
                printf("Dequeued from rear end: %d\n", dequeueRear(queue));
                break;
            case 4:
                printf("Dequeued from front end: %d\n", dequeueFront(queue));
                break;
            case 5:
                displayQueue(queue);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}




#27 add of Polynomial
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
struct Term {
    int coeff;
    int exp;
    struct Term* next;
};

// Function to create a new term
struct Term* createTerm(int coeff, int exp) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    if (newTerm == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newTerm->coeff = coeff;
    newTerm->exp = exp;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term at the end of a polynomial
void insertTerm(struct Term** poly, int coeff, int exp) {
    struct Term* newTerm = createTerm(coeff, exp);
    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        struct Term* current = *poly;
        while (current->next != NULL)
            current = current->next;
        current->next = newTerm;
    }
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coeff + poly2->coeff;
            if (sum != 0)
                insertTerm(&result, sum, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    // If there are remaining terms in either polynomial, add them to the result
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

// Function to display a polynomial
void displayPolynomial(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    int n, coeff, exp;
    
    // Create first polynomial
    struct Term* poly1 = NULL;
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &n);
    printf("Enter the coefficients and exponents for the first polynomial:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }
    printf("First polynomial: ");
    displayPolynomial(poly1);

    // Create second polynomial
    struct Term* poly2 = NULL;
    printf("\nEnter the number of terms in the second polynomial: ");
    scanf("%d", &n);
    printf("Enter the coefficients and exponents for the second polynomial:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }
    printf("Second polynomial: ");
    displayPolynomial(poly2);

    // Add the two polynomials
    struct Term* sum = addPolynomials(poly1, poly2);
    printf("\nSum of polynomials: ");
    displayPolynomial(sum);

    // Free allocated memory
    free(poly1);
    free(poly2);
    free(sum);

    return 0;
}



#28 Reverse() 

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

// Function to reverse a singly linked list
struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move pointers one position ahead
        current = next;
    }
    head = prev; // Update head to the last node
    return head;
}

// Function to display the elements of a singly linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int n, data;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);
    printf("Enter the elements of the list:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    printf("Original ");
    displayList(head);

    head = reverse(head);

    printf("Reversed ");
    displayList(head);

    return 0;
}



#29 DLL insert and delete

#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* getNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end
void insertAtEnd(struct Node** head_ref, int data) {
    struct Node* newNode = getNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to merge two sorted doubly linked lists
struct Node* mergeSortedLists(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Node* mergedHead = NULL;
    struct Node* tail = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            if (mergedHead == NULL) {
                mergedHead = head1;
                tail = head1;
            } else {
                tail->next = head1;
                head1->prev = tail;
                tail = head1;
            }
            head1 = head1->next;
        } else {
            if (mergedHead == NULL) {
                mergedHead = head2;
                tail = head2;
            } else {
                tail->next = head2;
                head2->prev = tail;
                tail = head2;
            }
            head2 = head2->next;
        }
    }

    if (head1 != NULL) {
        tail->next = head1;
        head1->prev = tail;
    }
    if (head2 != NULL) {
        tail->next = head2;
        head2->prev = tail;
    }

    return mergedHead;
}

// Function to print the doubly linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    int n, data;

    // Input for the first sorted doubly linked list
    printf("Enter the number of elements in the first sorted list: ");
    scanf("%d", &n);
    printf("Enter the elements of the first sorted list:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head1, data);
    }

    // Input for the second sorted doubly linked list
    printf("Enter the number of elements in the second sorted list: ");
    scanf("%d", &n);
    printf("Enter the elements of the second sorted list:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head2, data);
    }

    printf("First Sorted Doubly Linked List:\n");
    printList(head1);

    printf("Second Sorted Doubly Linked List:\n");
    printList(head2);
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
void insertBegin(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to insert a node at the end of the doubly linked list
void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
        newNode->prev = current;
    }
}

// Function to insert a node after a given node in the doubly linked list
void insertAfter(Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    if (prevNode->next != NULL)
        prevNode->next->prev = newNode;
    prevNode->next = newNode;
    newNode->prev = prevNode;
}

// Function to delete the first occurrence of a node with given key in the doubly linked list
void deleteNode(Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    Node* current = *head;
    // If the key is found in the first node itself
    if (current->data == key) {
        *head = current->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(current);
        return;
    }
    // Search for the node with the key
    while (current != NULL && current->data != key)
        current = current->next;
    // If the key is not found in the list
    if (current == NULL) {
        printf("Key not found in the list.\n");
        return;
    }
    // Remove the node
    if (current->prev != NULL)
        current->prev->next = current->next;
    if (current->next != NULL)
        current->next->prev = current->prev;
    free(current);
}

// Function to display the doubly linked list in forward direction
void displayForward(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Forward List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to display the doubly linked list in reverse direction
void displayBackward(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    // Move to the last node
    while (head->next != NULL)
        head = head->next;
    printf("Backward List: ");
    // Traverse backwards and print the data
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->prev;
    }
    printf("\n");
}

int main() {
    int numNodes, data;
    printf("Enter the number of nodes in the doubly linked list: ");
    scanf("%d", &numNodes);

    Node* head = NULL;

    // Insert at the beginning
    for (int i = 0; i < numNodes; ++i) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        insertBegin(&head, data);
    }

    displayForward(head);
    displayBackward(head);

    // Insert at the end
    printf("Enter data for the node to insert at the end: ");
    scanf("%d", &data);
    insertEnd(&head, data);

    displayForward(head);
    displayBackward(head);

    // Insert after a specific node
    printf("Enter data for the node to insert after: ");
    scanf("%d", &data);
    Node* current = head;
    while (current != NULL && current->data != data)
        current = current->next;
    if (current != NULL) {
        printf("Enter data for the new node: ");
        scanf("%d", &data);
        insertAfter(current, data);
    } else {
        printf("Node not found.\n");
    }

    displayForward(head);
    displayBackward(head);

    // Delete a node
    printf("Enter data of the node to delete: ");
    scanf("%d", &data);
    deleteNode(&head, data);

    displayForward(head);
    displayBackward(head);

    return 0;
}

    // Merge the two sorted doubly linked lists
    struct Node* mergedHead = mergeSortedLists(head1, head2);

    printf("Merged Sorted Doubly Linked List:\n");
    printList(mergedHead);

    return 0;
}




#30 merge sorted DLL

#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* getNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end
void insertAtEnd(struct Node** head_ref, int data) {
    struct Node* newNode = getNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to merge two sorted doubly linked lists
struct Node* mergeSortedLists(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Node* mergedHead = NULL;
    struct Node* tail = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            if (mergedHead == NULL) {
                mergedHead = head1;
                tail = head1;
            } else {
                tail->next = head1;
                head1->prev = tail;
                tail = head1;
            }
            head1 = head1->next;
        } else {
            if (mergedHead == NULL) {
                mergedHead = head2;
                tail = head2;
            } else {
                tail->next = head2;
                head2->prev = tail;
                tail = head2;
            }
            head2 = head2->next;
        }
    }

    if (head1 != NULL) {
        tail->next = head1;
        head1->prev = tail;
    }
    if (head2 != NULL) {
        tail->next = head2;
        head2->prev = tail;
    }

    return mergedHead;
}

// Function to print the doubly linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    int n, data;

    // Input for the first sorted doubly linked list
    printf("Enter the number of elements in the first sorted list: ");
    scanf("%d", &n);
    printf("Enter the elements of the first sorted list:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head1, data);
    }

    // Input for the second sorted doubly linked list
    printf("Enter the number of elements in the second sorted list: ");
    scanf("%d", &n);
    printf("Enter the elements of the second sorted list:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head2, data);
    }

    printf("First Sorted Doubly Linked List:\n");
    printList(head1);

    printf("Second Sorted Doubly Linked List:\n");
    printList(head2);

    // Merge the two sorted doubly linked lists
    struct Node* mergedHead = mergeSortedLists(head1, head2);

    printf("Merged Sorted Doubly Linked List:\n");
    printList(mergedHead);

    return 0;
}



#31 Postorder traversal

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left, *right;
    int data;
    int rightThread;
} Node;

Node *createNode(int item) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->data = item;
    node->rightThread = 0;
    return node;
}

void createThreaded(Node *root) {
    static Node *prev = NULL;
    if (root == NULL)
        return;
    createThreaded(root->left);
    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->rightThread = 1;
    }
    if (root->left == NULL)
        root->left = prev;
    prev = root;
    createThreaded(root->right);
}

// Function to find the rightmost node in a subtree
Node* rightmost(Node* node) {
    while (node != NULL && node->rightThread == 0 && node->right != NULL)
        node = node->right;
    return node;
}

// Function to find the postorder predecessor of a node
Node* postorderPredecessor(Node* node) {
    // If the node has a left child, the predecessor is the rightmost node of the left child
    if (node->left != NULL && node->left->right != node) {
        return rightmost(node->left);
    }
    // Otherwise, return the left child itself
    return node->left;
}

// Function to perform postorder traversal of the threaded binary tree
void postOrderTraversal(Node* root) {
    Node* curr = rightmost(root);
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = postorderPredecessor(curr);
    }
}

int main() {
    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    createThreaded(root);

    printf("Postorder traversal of the created threaded binary tree is: \n");
    postOrderTraversal(root);

    return 0;
}