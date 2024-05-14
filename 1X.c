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
