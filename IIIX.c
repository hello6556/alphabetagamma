#1 & #2 BST prepostcountdisplay,inorderdisplay
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    /* data */
    int data;
    struct Node *left, *right;
}Node;

typedef struct Stack
{
    /* data */
    Node** array;
    int capacity;
    int top;
}Stack;

typedef struct Queue
{
    Node **array;
    int front, rear;
    int capacity;
}Queue;

Queue *createQueue(int capacity)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->array = (Node**)malloc(queue->capacity * sizeof(Queue*));
    return queue;
}

int queueEmpty(Queue* queue)
{
    return queue->front == -1;
}

void enqueue(Queue* queue, Node* root)
{
    if(queue->rear == queue->capacity -1)
        return;
    queue->array[++queue->rear] = root;
    if(queue->front == -1)
        queue->front = 0;
}

Node* dequeue(Queue* queue)
{
    if(queueEmpty(queue))
        return NULL;
    Node* item = queue->array[queue->front];
    if(queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return item;
}

Stack* createStack(int capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Node**)malloc(stack->capacity * sizeof(Node*));
    return stack;
}

int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

void push(Stack* stack, Node* item)
{
    if(isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

Node* pop(Stack* stack)
{
    if(isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

Node* newNode(int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp; // Missing return statement added
}

Node* insert(Node* root, int data)
{
    if(root == NULL)
    {
        root = newNode(data);
        return root;
    }

    Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while(front != rear)
    {
        Node* temp = queue[front++];

        if(temp->left == NULL)
        {
            temp->left = newNode(data);
            break;
        }
        else 
            queue[rear++] = temp->left;
        
        if(temp->right == NULL)
        {
            temp->right = newNode(data);
            break;
        }

        else
            queue[rear++] = temp->right;
    }
    return root;
}

void inOrder(Node* root)
{
    if(root == NULL)
        return;
    
    Stack* stack = createStack(100);
    Node* current = root;

    while (current != NULL || !isEmpty(stack))
    {
        while (current != NULL)
        {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ",current->data);

        current = current->right;
    }
}

void preOrder(Node* root)
{
    if(root == NULL)
        return;

    Stack* stack = createStack(100);
    Node* current = root;
    push(stack, current);

    while (!isEmpty(stack))
    {
        current = pop(stack);
        printf("%d ",current->data);

        if(current->right)
            push(stack, current->right);
        if(current->left)
            push(stack, current->left);
    }
}

void postOrder(Node* root)
{
    if(!root)
        return;

    Stack* stack1 = createStack(100);
    Stack* stack2 = createStack(100);

    Node* current = root;
    push(stack1, current);

    while (!isEmpty(stack1))
    {
        current = pop(stack1);
        push(stack2, current);

        if(current->left)
            push(stack1, current->left);
        if(current->right)
            push(stack1, current->right);
    }

    while(!isEmpty(stack2))
    {
        current = pop(stack2);
        printf("%d ",current->data);
    }
}

void displayLevelWise(Node* root)
{
    if(root == NULL)
        return;

    Queue* queue = createQueue(100);
    enqueue(queue, root);
    while (!queueEmpty(queue))
    {
        int nodeCount = queue->rear - queue->front + 1;
        while (nodeCount > 0)
        {
            Node* temp  = dequeue(queue);
            printf("%d ",temp->data);
            if(temp->left != NULL)
                enqueue(queue, temp->left);
            if(temp->right != NULL)
                enqueue(queue, temp->right);
            nodeCount--;
        }
        printf("\n");
    }
}


int heightOfBTree(Node* root)
{
    if(root == NULL)
        return 0;
    Queue* queue = createQueue(100);
    enqueue(queue, root);
    int height = 0;

    while (!queueEmpty(queue))
    {
        int nodeCount = queue->rear - queue->front + 1;
        height++;

        while (nodeCount>0)
        {
            Node* temp = dequeue(queue);
            if(temp->left != NULL)
                enqueue(queue,temp->left);
            if(temp->right != NULL)
                enqueue(queue, temp->right);
            nodeCount--;
        }
    }
    return height;
}


int main()
{
    Node* root = NULL;
    int value, nodes;
    printf("Enter the number of nodes you want to insert: ");
    scanf("%d", &nodes);

    printf("Enter %d values to insert into the binary tree:\n", nodes);
    for (int i = 0; i < nodes; ++i) {
        printf("Node %d: ", i + 1);
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Preorder: ");
    preOrder(root);

    printf("\nInorder: ");
    inOrder(root);

    printf("\nPostorder: ");
    postOrder(root);

    printf("\nTotal number of nodes: %d",getFullCount(root));

    printf("\nHeight of binary tree is: %d",heightOfBTree(root));

    printf("\nNumber of nodes on longest path is: %d",countNodesOnLongPath(root));

    printf("\nLevelwise Display: \n");
    displayLevelWise(root);
    
    return 0;
}

#1 & #3

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left, *right;
}Node;

typedef struct Stack
{
    Node** array;
    int capacity;
    int top;
}Stack;

typedef struct Queue
{
    Node **array;
    int front, rear;
    int capacity;
}Queue;

Queue *createQueue(int capacity)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->array = (Node**)malloc(queue->capacity * sizeof(Queue*));
    return queue;
}

int queueEmpty(Queue* queue)
{
    return queue->front == -1;
}

void enqueue(Queue* queue, Node* root)
{
    if(queue->rear == queue->capacity -1)
        return;
    queue->array[++queue->rear] = root;
    if(queue->front == -1)
        queue->front = 0;
}

Node* dequeue(Queue* queue)
{
    if(queueEmpty(queue))
        return NULL;
    Node* item = queue->array[queue->front];
    if(queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return item;
}

Stack* createStack(int capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Node**)malloc(stack->capacity * sizeof(Node*));
    return stack;
}

int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

void push(Stack* stack, Node* item)
{
    if(isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

Node* pop(Stack* stack)
{
    if(isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

Node* newNode(int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
}

Node* insert(Node* root, int data)
{
    if(root == NULL)
    {
        root = newNode(data);
        return root;
    }

    Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while(front != rear)
    {
        Node* temp = queue[front++];

        if(temp->left == NULL)
        {
            temp->left = newNode(data);
            break;
        }
        else 
            queue[rear++] = temp->left;
        
        if(temp->right == NULL)
        {
            temp->right = newNode(data);
            break;
        }

        else
            queue[rear++] = temp->right;
    }
    return root;
}

void inOrder(Node* root)
{
    if(root == NULL)
        return;
    
    Stack* stack = createStack(100);
    Node* current = root;

    while (current != NULL || !isEmpty(stack))
    {
        while (current != NULL)
        {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ",current->data);

        current = current->right;
    }
}

void preOrder(Node* root)
{
    if(root == NULL)
        return;

    Stack* stack = createStack(100);
    Node* current = root;
    push(stack, current);

    while (!isEmpty(stack))
    {
        current = pop(stack);
        printf("%d ",current->data);

        if(current->right)
            push(stack, current->right);
        if(current->left)
            push(stack, current->left);
    }
    
}

void postOrder(Node* root)
{
    if(!root)
        return;

    Stack* stack1 = createStack(100);
    Stack* stack2 = createStack(100);

    Node* current = root;
    push(stack1, current);

    while (!isEmpty(stack1))
    {
        current = pop(stack1);
        push(stack2, current);

        if(current->left)
            push(stack1, current->left);
        if(current->right)
            push(stack1, current->right);
    }

    while(!isEmpty(stack2))
    {
        current = pop(stack2);
        printf("%d ",current->data);
    }
    
}

void displayLevelWise(Node* root)
{
    if(root == NULL)
        return;

    Queue* queue = createQueue(100);
    int front = -1, rear = -1;
    enqueue(queue, root);
    while (!queueEmpty(queue))
    {
        int nodeCount = queue->rear - queue->front + 1;
        while (nodeCount > 0)
        {
            Node* temp  = dequeue(queue);
            printf("%d ",temp->data);
            if(temp->left != NULL)
                enqueue(queue, temp->left);
            if(temp->right != NULL)
                enqueue(queue, temp->right);
            nodeCount--;
        }
        printf("\n");
    }
    
}

int getFullCount(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }

    int count = 0;
    Node* queue[100];
    int front = -1, rear = -1; //change to 0 if doesnt work
    queue[++rear] = root;
    while (front != rear)
    {
        Node* temp = queue[++front];
        count++;

        if(temp->left != NULL)
            queue[++rear] = temp->left;
        if(temp->right != NULL)
            queue[++rear] = temp->right;
    }
    //free(queue);
    return count;
    
}

int heightOfBTree(Node* root)
{
    if(root == NULL)
        return 0;
    
    Queue* queue = createQueue(100);
    enqueue(queue, root);
    int height = 0;

    while (!queueEmpty(queue))
    {
        int nodeCount = queue->rear - queue->front + 1;
        height++;

        while (nodeCount>0)
        {
            Node* temp = dequeue(queue);
            if(temp->left != NULL)
                enqueue(queue,temp->left);
            if(temp->right != NULL)
                enqueue(queue, temp->right);
            nodeCount--;
        }
    }
    return height;
}

int countNodesOnLongPath(Node *root)
{
    if(root == NULL)
        return 0;

        Queue* queue = createQueue(100);
        enqueue(queue, root);
        int nodeCount = 0;

        while (!queueEmpty(queue))
        {
            /* code */
            int levelNodeCount = queue->rear - queue->front + 1;
            if(nodeCount < levelNodeCount)
                nodeCount = levelNodeCount;

            while (levelNodeCount > 0)
            {
                /* code */
                Node* temp = dequeue(queue);
                if(temp->left != NULL)
                    enqueue(queue, temp->left);
                if(temp->right != NULL)
                    enqueue(queue, temp->right);
                levelNodeCount--;
            }
        }
        return nodeCount+1;
}

int main()
{
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);

    printf("Preorder: ");
    preOrder(root);

    printf("\nInorder: ");
    inOrder(root);

    printf("\nPostorder: ");
    postOrder(root);

    printf("\nTotal number of nodes: %d",getFullCount(root));

    printf("\nHeight of binary tree is: %d",heightOfBTree(root));

    printf("\nNumber of nodes on longest path is: %d",countNodesOnLongPath(root));

    printf("\nLevelwise Display: \n");
    displayLevelWise(root);
}





#3 to #10 BST crdedimirror


#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = key;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
    {
        return newNode(key);
    }

    struct Node* current = root;
    struct Node* parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if(key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    if(key < parent->data)
        parent->left = newNode(key);
    else
        parent->right = newNode(key);
    return root;
}

void levelOrder(struct Node *root)
{
    if(root == NULL)
        return;

    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while(front != rear)
    {
        struct Node* temp = queue[++front];
        printf("%d ",temp->data);

        if(temp->left != NULL)
            queue[++rear] = temp->left;
        if(temp->right != NULL)
            queue[++rear] = temp->right;
        printf("\n");
    }
}

void mirrorImage(struct Node *root)
{
    if(root == NULL)
        return;

    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while(front != rear)
    {
        struct Node* temp = queue[++front];
        printf("%d ",temp->data);

        if(temp->right != NULL)
            queue[++rear] = temp->right;
        if(temp->left != NULL)
            queue[++rear] = temp->left;
    }
}

int height(struct Node* root)
{
    if(root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight) ? (leftHeight+1) : (rightHeight+1);
}

struct Node* find(struct Node* root, int val)
{
    struct Node* current = root;

    while(current != NULL)
    {
        if(val == current->data)
            return current;
        else if(val < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

struct Node* findMin(struct Node* node)
{
    struct Node* current = node;
    while(current != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key)
{
    if(root == NULL)
        return root;
    if(key < root->data)
        root->left = deleteNode(root->left, key);
    else if(key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if(root->left == NULL)
        {

            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(struct Node* root) {
    if(root == NULL)
        return;
    struct Node* current = root;
    struct Node* stack[100];
    int top = -1;

    while(current != NULL || top !=-1)
    {
        while(current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ",current->data);
        current = current->right;
    }

}

void preOrder(struct Node* root)
{

    if(root == NULL)
        return;
    struct Node* current = root;
    struct Node* stack[100];
    int top = -1;

    while(current != NULL || top != -1)
    {
        while(current != NULL)
        {
            stack[++top] = current;
            printf("%d ",current->data);
            current = current->left;
        }
        current = stack[top--];
        current = current->right;
    }
}

void postOrder(struct Node* root)
{
    if(root == NULL)
        return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while(top1 != -1)
    {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;

        if(current->left != NULL)
            stack1[++top1] = current->left;
        if(current->right != NULL)
            stack1[++top1] = current->right;
    }

    while(top2 != -1)
    {
        printf("%d ",stack2[top2--]->data);
    }
}

int countLeafNodes(struct Node* root)
{
    if(root == NULL)
        return 0;
    int count = 0;
    struct Node* stack[100];
    int top = -1;
    while(1)
    {
        while(root != NULL)
        {
            stack[++top] = root;
            root = root->left;
        }
        if(top == -1)
            break;
        root = stack[top--];

        if(root->left == NULL && root->right == NULL)
            count++;

        root = root->right;
    }
    return count;
}

int totalNodes(struct Node* root)
{
    if(root == NULL)
        return 0;
    int count = 0;
    struct Node* stack[100];
    int top = -1;
    while(1)
    {
        while(root != NULL)
        {
            stack[++top] = root;
            root = root->left;
            count++;
        }
        if(top == -1)
            break;
        root = stack[top--];


        root = root->right;
    }
    return count;
}

int main()
{
    struct Node* root = NULL;

    root = insert(root,50);
    root = insert(root,30);
    root = insert(root,20);
    root = insert(root,40);
    root = insert(root,70);
    root = insert(root,60);
    root = insert(root,80);

    printf("Level Wise display of the tree: ");
    levelOrder(root);
    printf("\n");

    printf("Mirror Image of the tree: ");
    mirrorImage(root);

    printf("\n");

    printf("Height of the tree: %d",height(root));

    int f;
    printf("\nEnter key to search: ");
    scanf("%d",&f);
    struct Node* found = find(root,f);
    if(found != NULL)
        printf("\nKey %d found",f);
    else
        printf("\nNode not found");

    printf("\nInorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preOrder(root);

    printf("\nPostorder: ");
    postOrder(root);

    printf("\nTotal Number of nodes: %d",totalNodes(root));

    printf("\nTotal number of leaf nodes: %d",countLeafNodes(root));


    /*printf("\nEnter the value to be deleted: ");
    int new;
    scanf("%d",&new);
    root = deleteNode(root,new);*/

    return 0;
}




#3 to #10
#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = key;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
    {
        return newNode(key);
    }

    struct Node* current = root;
    struct Node* parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if(key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    if(key < parent->data)
        parent->left = newNode(key);
    else
        parent->right = newNode(key);
    return root;
}

void levelOrder(struct Node *root)
{
    if(root == NULL)
        return;

    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while(front != rear)
    {
        struct Node* temp = queue[++front];
        printf("%d ",temp->data);

        if(temp->left != NULL)
            queue[++rear] = temp->left;
        if(temp->right != NULL)
            queue[++rear] = temp->right;
        printf("\n");
    }
}

void mirrorImage(struct Node *root)
{
    if(root == NULL)
        return;

    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while(front != rear)
    {
        struct Node* temp = queue[++front];
        printf("%d ",temp->data);

        if(temp->right != NULL)
            queue[++rear] = temp->right;
        if(temp->left != NULL)
            queue[++rear] = temp->left;
    }
}

int height(struct Node* root)
{
    if(root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight) ? (leftHeight+1) : (rightHeight+1);
}

struct Node* find(struct Node* root, int val)
{
    struct Node* current = root;

    while(current != NULL)
    {
        if(val == current->data)
            return current;
        else if(val < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

struct Node* findMin(struct Node* node)
{
    struct Node* current = node;
    while(current != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key)
{
    if(root == NULL)
        return root;
    if(key < root->data)
        root->left = deleteNode(root->left, key);
    else if(key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if(root->left == NULL)
        {

            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(struct Node* root) {
    if(root == NULL)
        return;
    struct Node* current = root;
    struct Node* stack[100];
    int top = -1;

    while(current != NULL || top !=-1)
    {
        while(current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ",current->data);
        current = current->right;
    }

}

void preOrder(struct Node* root)
{

    if(root == NULL)
        return;
    struct Node* current = root;
    struct Node* stack[100];
    int top = -1;

    while(current != NULL || top != -1)
    {
        while(current != NULL)
        {
            stack[++top] = current;
            printf("%d ",current->data);
            current = current->left;
        }
        current = stack[top--];
        current = current->right;
    }
}

void postOrder(struct Node* root)
{
    if(root == NULL)
        return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while(top1 != -1)
    {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;

        if(current->left != NULL)
            stack1[++top1] = current->left;
        if(current->right != NULL)
            stack1[++top1] = current->right;
    }

    while(top2 != -1)
    {
        printf("%d ",stack2[top2--]->data);
    }
}

int countLeafNodes(struct Node* root)
{
    if(root == NULL)
        return 0;
    int count = 0;
    struct Node* stack[100];
    int top = -1;
    while(1)
    {
        while(root != NULL)
        {
            stack[++top] = root;
            root = root->left;
        }
        if(top == -1)
            break;
        root = stack[top--];

        if(root->left == NULL && root->right == NULL)
            count++;

        root = root->right;
    }
    return count;
}

int totalNodes(struct Node* root)
{
    if(root == NULL)
        return 0;
    int count = 0;
    struct Node* stack[100];
    int top = -1;
    while(1)
    {
        while(root != NULL)
        {
            stack[++top] = root;
            root = root->left;
            count++;
        }
        if(top == -1)
            break;
        root = stack[top--];


        root = root->right;
    }
    return count;
}

int main()
{
    struct Node* root = NULL;

    int nodes, key;
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the elements to be inserted: ");
    for(int i = 0; i < nodes; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Level Wise display of the tree: ");
    levelOrder(root);
    printf("\n");

    printf("Mirror Image of the tree: ");
    mirrorImage(root);

    printf("\n");

    printf("Height of the tree: %d",height(root));

    int f;
    printf("\nEnter key to search: ");
    scanf("%d",&f);
    struct Node* found = find(root,f);
    if(found != NULL)
        printf("\nKey %d found",f);
    else
        printf("\nNode not found");

    printf("\nInorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preOrder(root);

    printf("\nPostorder: ");
    postOrder(root);

    printf("\nTotal Number of nodes: %d",totalNodes(root));

    printf("\nTotal number of leaf nodes: %d",countLeafNodes(root));

    return 0;
}


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