#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int height;
    int balance;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int item) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->height = 1;
    return temp;
}

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
    {
        node->left = insert(node->left, key);
        node->left->parent = node;
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
        node->right->parent = node;
    }

    return node;
}

Node* findMin(Node* node) {
    Node* current = node;

    while (current && current->left != NULL) {
        printf("%d -> ", current->key);
        current = current->left;
    }
    if (current != NULL)
        printf("%d\n", current->key);

    return current;
}

Node* findMax(Node* node) {
    Node* current = node;
    while (current && current->right != NULL) {
        printf("%d -> ", current->key);
        current = current->right;
    }

    if (current != NULL)
        printf("%d\n", current->key);

    return current;
}

int findLevel(Node* node, int key, int level) {
    if (node == NULL)
        return 0;
    if (node->key == key)
        return level;

    int downlevel = findLevel(node->left, key, level + 1);
    if (downlevel != 0)
        return downlevel;

    downlevel = findLevel(node->right, key, level + 1);
    return downlevel;
}

void reverseInorder(Node* node) {
    if (node == NULL)
        return;

    reverseInorder(node->right);
    printf("%d ", node->key);
    reverseInorder(node->left);
}

void printDescending(Node* root) {
    printf("Tree elements in descending order: ");
    reverseInorder(root);
    printf("\n");
}

void printPreorder(Node* node) {
    if (node == NULL)
        return;

    printf("%d ", node->key);
    printPreorder(node->left);
    printPreorder(node->right);
}

int getHeight(Node* node) {
    if (node == NULL)
        return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int printSubtreeAndHeight(Node* node, int key, int level) {
    if (node == NULL)
        return -1;

    if (node->key == key) {
        printf("Subtree with root %d in pre-order order: ", node->key);
        printPreorder(node);
        printf("\n");
        return getHeight(node);
    }

    int subtreeHeight = printSubtreeAndHeight(node->left, key, level + 1);
    if (subtreeHeight == -1)
        subtreeHeight = printSubtreeAndHeight(node->right, key, level + 1);

    return subtreeHeight;
}

Node* deleteSubtree(Node* root) {
    if (root == NULL)
        return 0;

    deleteSubtree(root->left);
    deleteSubtree(root->right);

    root->left = NULL;
    root->right = NULL;
    if (root->parent != NULL)
    {
        if (root->parent->left != NULL)
        {
            if (root->parent->left->key == root->key) root->parent->left = NULL;
        }
        if (root->parent->right != NULL)
        {
            if (root->parent->right->key == root->key) root->parent->right = NULL;
        }
    }
    free(root);
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

Node* deleteTree(Node* node) {
    if (node == NULL)
        return NULL;

    node->left = deleteTree(node->left);
    node->right = deleteTree(node->right);
    free(node);
    return NULL;
}

void printNodesAtLevel(struct Node* root, int level, int currentLevel) {
    if (root == NULL)
        return;

    if (currentLevel == level) {
        printf("%d ", root->key);
        //ot = deleteNode(root, root->key);
    }
    else {
        printNodesAtLevel(root->left, level, currentLevel + 1);
        printNodesAtLevel(root->right, level, currentLevel + 1);
    }
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;   // Копируем содержимое узла temp в узел root
            free(temp);
        }
        else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}

void printBst(struct Node* root, int level)
{
    if (root != NULL)
    {
        printf("\nLevel: %d\n", level + 1);
        printf("Key: %d\n", root->key);
        if (root->right != NULL) printf("Right: %d\n", root->right->key);
        if (root->left != NULL) printf("Left: %d\n", root->left->key);
        printBst(root->right, level + 1);
        printBst(root->left, level + 1);
    }
}

struct Node* getNode(struct Node* root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->key == key)
        return root;

    if (key < root->key)
        return getNode(root->left, key);

    return getNode(root->right, key);
}

int getHeightOfSubtree(struct Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = getHeightOfSubtree(root->left);
    int rightHeight = getHeightOfSubtree(root->right);
    return 1 + max(leftHeight, rightHeight);
}

void getBalances(struct Node* root) {
    if (root == NULL)
        return;
    root->balance = getHeightOfSubtree(root->left) - getHeightOfSubtree(root->right);
    printPreorder(root->left);
    printPreorder(root->right);
}


struct Node* replaceWithHigherChild(Node* root) {
    if (getHeightOfSubtree(root->right) > getHeightOfSubtree(root->left))
    {
        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    else
    {
        struct Node* temp = minValueNode(root->left);
        root->key = temp->key;
        root->left = deleteNode(root->left, temp->key);
    }
    return root;
}

int checkCurrentLevel(Node* root, int level, Node* treeRoot)
{
    if (root == NULL)
    {
        return 0;
    }
    if (level == 1)
    {
//        printf("\n%d", root->key);
        int balanceFactor = getHeightOfSubtree(root->left) - getHeightOfSubtree(root->right);
        if (abs(balanceFactor) > 1)
        {
            int key = root->key;
            root = replaceWithHigherChild(root);
            insert(treeRoot, key);
            return 1;
        }
    }
    else if (level > 1)
    {
        checkCurrentLevel(root->left, level - 1, treeRoot);
        checkCurrentLevel(root->right, level - 1, treeRoot);
    }
    return 0;
}

void balance(Node* root, int h)
{
    int i;
    int wasBalanced = 0;
    while(1)
    {
        wasBalanced = 0;

        for (i = 1; i <= h; i++)
        {
            wasBalanced = checkCurrentLevel(root, i, root);
            if(wasBalanced) break;
            //printf("\n%d", i);
        }

        if (wasBalanced == 0) break;
    }
}

int bstToVine(Node* grand)
{
    int count = 0;
    Node* tmp = grand->right;
    while (tmp) {
        if (tmp->left) {
            Node* oldTmp = tmp;
            tmp = tmp->left;
            oldTmp->left = tmp->right;
            tmp->right = oldTmp;
            grand->right = tmp;
        }
        else {
            count++;
            grand = tmp;
            tmp = tmp->right;
        }
    }

    return count;
}

void compress(Node* grand, int m)
{
    Node* tmp = grand->right;

    for (int i = 0; i < m; i++) {
        Node* oldTmp = tmp;
        tmp = tmp->right;
        grand->right = tmp;
        oldTmp->right = tmp->left;
        tmp->left = oldTmp;
        grand = tmp;
        tmp = tmp->right;
    }
}

Node* balanceBST(Node* root)
{
    Node* grand = newNode(0);
    grand->right = root;      //prawy potomek 0 - to jest Pozostałe drzewo

    int count = bstToVine(grand);   //right rotate

    int h = log2(count + 1);   // wysokosc gdzie wszytkie nodes maja potomkow
    int m = pow(2, h) - 1;  //liczby węzłów na wszystkich poziomach drzewa z wyjątkiem ostatniego

    compress(grand, count - m);   //left rotate   (..., Liczba węzłów na ostatnim poziomie drzewa)

    for (m = m / 2; m > 0; m /= 2) {
        compress(grand, m);
    }

    // return the balanced tree
    return grand->right;
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

double what_time_is_it() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec * 1e-9;
}

#endif

// Funkcja wy�wietlaj�ca menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Find the element with the smallest value in the tree\n");
    printf("2. Find the element with the highest value in the tree\n");
    printf("3. Find the level of the node with the specified key, print the elements at this level and delete the node\n");
    printf("4. Print all tree elements in descending order\n");
    printf("5. Write the subtree in pre-order order, specify the height and delete it\n");
    printf("6. Balance the tree and list items before and after balancing\n");
    printf("7. Exit\n");
    printf("Select an option: ");
}

int main() {
    Node* root = NULL;
    int n, i, choice, key, num;
    char ch;
    double min_time = 0, max_time = 0, balance_time = 0, print_time = 0;
    double start, end;
    srand(time(NULL));

    printf("Want to generate numbers or input by yourself? (g/i):");
    scanf(" %c", &ch);
    if (ch == 'g') {
        printf("Enter the number of items to generate (n <= 15): ");
        scanf("%d", &n);
        printf("Generated numbers: ");
        for (i = 0; i < n; ++i) {
            num = rand() % 100 + 1;
            printf("%d ", num);
            root = insert(root, num);
        }
        printf("\n");
    }
    else if (ch == 'i') {
        printf("Enter the number of items to input (n <= 15): ");
        scanf("%d", &n);
        printf("Enter %d numbers: ", n);
        for (i = 0; i < n; ++i) {
            scanf("%d", &num);
            root = insert(root, num);
        }
    }
    else {
        printf("Invalid choice.\n");
        return 1;
    }

    do {
        displayMenu();
        scanf("%d", &choice);


        switch (choice) {
            case 1: {
                printf("Path to the element with the smallest value: ");
                start = what_time_is_it();
                findMin(root);
                end = what_time_is_it();
                min_time += (end - start);
                printf("Time: %lf\n", min_time);
                break;
            }
            case 2: {
                printf("Path to the element with the highest value: ");
                start = what_time_is_it();
                findMax(root);
                end = what_time_is_it();
                max_time += (end - start);
                printf("Time: %lf\n", max_time);
                break;
            }
            case 3: {
                printf("Enter the node key to delete: ");
                scanf("%d", &key);
                int level = findLevel(root, key, 1);
                if (level != -1) {
                    printf("The node with the key %d is at %d level\n", key, level);
                    printf("Elements at the level %d: ", level);
                    printNodesAtLevel(root, level, 1);
                    printf("\n");
                    deleteNode(root, key);
//                    getBalances(root);
                }
                else {
                    printf("Node with key %d not found in tree.\n", key);
                }
                break;
            }
            case 4: {
                start = what_time_is_it();
                printDescending(root);
                end = what_time_is_it();
                print_time += (end - start);
                printf("Time: %lf\n", print_time);
                break;
            }
            case 5: {
                printf("Enter the value of the root: ");
                scanf("%d", &key);
                struct Node* subtreeRoot = getNode(root, key);
                if (subtreeRoot != NULL)
                {
                    printf("Subtree in Preorder: ");
                    printPreorder(subtreeRoot);
                    printf("\n");
                    int subtreeHeight = getHeightOfSubtree(subtreeRoot);
                    printf("Subtree height: %d\n", subtreeHeight);
                    deleteSubtree(subtreeRoot);
                    printf("Removed subtree.\n");
                }
//                getBalances(root);
                break;
            }
            case 6: {
                printf("Tree before balancing:");
                printPreorder(root);
                printf("\n");
                int c;
                int h = getHeightOfSubtree(root);
                printf("Balancing with DSW or removing the roots of subtrees? (1/2):");
                scanf("%d", &c);
                if (c==1) {
                    start = what_time_is_it();
                    root = balanceBST(root);
                    end = what_time_is_it();
                    balance_time += (end - start);
                    printf("Time: %lf", balance_time);
//                    printf("\nBalance:");
//                    getBalances(root);
                }
                else if (c==2) {
                    start = what_time_is_it();
                    balance(root, h);
                    end = what_time_is_it();
                    balance_time += (end - start);
                    printf("Time: %lf", balance_time);
//                    printf("Balance:");
//                    getBalances(root);
                }
                printf("\n");
                printf("Tree after balancing:");
                printPreorder(root);
                printf("\n");
                break;
            }
            case 7:
            {
                break;
            }
            case 8:
            {
                printBst(root, 0);
                break;
            }
            default:
                printf("Wrong option. Try again.\n");
        }
    } while (choice != 7);

    root = deleteTree(root);

    return 0;
}