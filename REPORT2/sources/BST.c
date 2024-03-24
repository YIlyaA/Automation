#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct Node {
    int key;
    struct Node* left, * right;
} Node;

Node* newNode(int item) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

Node* balanceNode(Node* node) {
    int balance = height(node->left) - height(node->right);

    if (balance > 1) {
        if (height(node->left->left) >= height(node->left->right))
            return rotateRight(node);
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (balance < -1) {
        if (height(node->right->right) >= height(node->right->left))
            return rotateLeft(node);
        else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}


Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

Node* findMin(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }

    if (current != NULL)
        return current;
}

#ifdef _WIN32
#include <Windows.h>
double what_time_is_it()
{
    FILETIME ft;
    ULONGLONG nTime100;
    GetSystemTimeAsFileTime(&ft);
    nTime100 = ((ULONGLONG)ft.dwHighDateTime << 32) + ft.dwLowDateTime;
    return (double)nTime100 * 1e-9;
}
#else
#include <time.h>
double what_time_is_it()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec * 1e-9;
}
#endif


int main() {
    Node* root = NULL;
    int n, i, num;
    double create_time = 0;
    double balance_time = 0;
    double find_min_time = 0;
    double start;
    double end;

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &num);
//        printf("%d ", num);
        start = what_time_is_it();
        root = insert(root, num);
        end = what_time_is_it();
        create_time += (end - start);
    }
//    printf("\n");
    start = what_time_is_it();
    balanceNode(root);
    end = what_time_is_it();
    balance_time += (end - start);
    start = what_time_is_it();
    findMin(root);
//    Node* minNode = findMin(root);  # output min value
//    printf("%d\n", minNode->key);
    end = what_time_is_it();
    find_min_time += (end - start);
    printf("create_time: %.15f\n", create_time);
    printf("balance_time: %.15f\n", balance_time);
    printf("find_min_time: %.15f\n", find_min_time);
    return 0;
}