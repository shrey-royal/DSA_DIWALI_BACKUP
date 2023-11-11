#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct ListNode {
    int data;
    struct ListNode* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if(root == NULL) return createNode(data);

    if(data < root->data) {
        root->left = insert(root->left, data);
    } else if(data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

void inorder(struct Node* root) {
    if(root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if(root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if(root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

struct Node* search(struct Node* root, int value) {
    if(root == NULL || root->data == value) return root;

    if(value < root->data) return search(root->left, value);

    return search(root->right, value);
}

int height(struct Node* root) {
    if(root == NULL) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void levelOrderTraversal(struct Node* root) {
    if(root == NULL) return;

    //using queue
    struct Node* queue[10];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while(front < rear) {
        struct Node* current = queue[front++];

        printf("%d ", current->data);

        if(current->left != NULL) queue[rear++] = current->left;
        if(current->right != NULL) queue[rear++] = current->right;
    }
}

struct Node* deleteNode(struct Node* root, int data) {
    if(root == NULL) return root;

    if(data < root->data) root->left = deleteNode(root->left, data);
    else if(data > root->data) root->right = deleteNode(root->right, data);
    else {
        if(root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while(temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void findMinMax(struct Node* root, int* min, int* max) {
    if(root == NULL) return;

    if(root->data < *min) *min = root->data;
    if(root->data > *max) *max = root->data;

    findMinMax(root->left, min, max);
    findMinMax(root->right, min, max);
}

void subtreeOperations(struct Node* root) {
    if(root != NULL) {
        printf("\nPerforming subtree operation on node with data: %d\n", root->data);

        printf("%d  ", root->data);
        subtreeOperations(root->left);
        subtreeOperations(root->right); 
    }
}

//for ll
void insertAtEnd(struct ListNode** head, int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = value;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        return;
    }

    struct ListNode* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void convertBSTtoLinkedList(struct Node* root, struct ListNode** head) {
    if(root == NULL) return;

    convertBSTtoLinkedList(root->left, head);
    insertAtEnd(head, root->data);
    convertBSTtoLinkedList(root->right, head);
}

void printListFromBeginning(struct ListNode* head) {
    if(head == NULL) {
        printf("\nList is Empty!");
        return;
    }

    struct ListNode* temp = head;

    printf("\nList: ");
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void serializeTree(struct Node* root, FILE *fp) {
    if(root == NULL) {
        // printf("N ");
        fprintf(fp, "N ");  //N -> null
        return;
    }

    // printf("%d ", root->data);
    fprintf(fp, "%d ", root->data);
    serializeTree(root->left, fp);
    serializeTree(root->right, fp);
}

struct Node* deserializeTree(FILE *fp) {
    char token[10];
    fscanf(fp, "%s", token);

    if(strcmp(token, "N") == 0) return NULL;

    int data = atoi(token);
    struct Node* root = createNode(data);

    root->left = deserializeTree(fp);
    root->right = deserializeTree(fp);

    return root;
}

struct Node* findLCA(struct Node* root, int n1, int n2) {
    if(root == NULL || root->data == n1 || root->data == n2) return root;

    struct Node* leftLCA = findLCA(root->left, n1, n2);
    struct Node* rightLCA = findLCA(root->right, n1, n2);

    if(leftLCA != NULL && rightLCA != NULL) return root;

    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

void pruneTree(struct Node** root) {
    if(*root != NULL) {
        pruneTree(&((*root)->left));
        pruneTree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

void printTree(struct Node* root, int space) {
    //Base case
    if(root == NULL) {
        // printf("\nTree is empty.");
        return;
    }

    //Increase distance between levels
    space += 4;

    //Process right child first
    printTree(root->right, space);

    //Print current node after space
    for (int i = 4; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    //process left child
    printTree(root->left, space);
}


// 1 8 1 3 1 10 1 1 1 6 1 14 1 4 1 7 1 13
int main() {
    FILE *fp = NULL;
    struct ListNode* head = NULL;
    struct Node* root = NULL;
    int choice, data, min, max;

    do {
        system("cls");  //clrscr
        printTree(root, 0);
        printf("\n\nBinary Tree Operations Menu\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");   //left, root, right
        printf("3. Preorder Traversal\n");  //root, left, right
        printf("4. Postorder Traversal\n"); //left, right, root
        printf("5. Search\n");
        printf("6. Height\n");
        printf("7. Level Order Traversal\n");
        printf("8. Delete\n");
        printf("9. Find Min and Max\n");
        printf("10. convertBSTtoLinkedList\n");
        printf("11. Serialize Tree\n");
        printf("12. Deserialize Tree\n");
        printf("13. Find LCA\n");
        printf("14. Prune Tree\n");
        printf("15. Display Tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;

            case 2:
                printf("Inorder Traversal : ");
                inorder(root);
                printf("\n");
                system("pause");    //getch();
                break;

            case 3:
                printf("Preorder Traversal : ");
                preorder(root);
                printf("\n");
                system("pause");    //getch();
                break;

            case 4:
                printf("Postorder Traversal : ");
                postorder(root);
                printf("\n");
                system("pause");    //getch();
                break;

            case 5:
                printf("\nPlease enter a value to search: ");
                scanf("%d", &data);
                if(search(root, data) != NULL) {
                    printf("\nKey %d found in the tree.\n", data);
                } else {
                    printf("\nKey %d not found in the tree.\n", data);
                }
                system("pause");
                break;

            case 6:
                printf("\nHeight of the Tree: %d\n", height(root));
                system("pause");
                break;

            case 7:
                printf("\nLevel Order Traversal: ");
                levelOrderTraversal(root);
                printf("\n");
                system("pause");
                break;

            case 8:
                printf("\nEnter value to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;

            case 9:
                min = INT_MAX;
                max = INT_MIN;
                findMinMax(root, &min, &max);
                printf("\nMinimum value in the tree: %d", min);
                printf("\nMaximum value in the tree: %d\n", max);
                system("pause");
                break;
            
            case 10:
                convertBSTtoLinkedList(root, &head);
                printListFromBeginning(head);
                system("pause");
                break;
            
            case 11:
                fp = fopen("store_tree.txt", "w");
                if(fp == NULL) {
                    fprintf(stderr, "\nError opening file for writing.\n");
                    return 1;
                }
                serializeTree(root, fp);
                fclose(fp);
                printf("\n");
                system("pause");
                break;
            
            case 12:
                fp = fopen("store_tree.txt", "r");
                if(fp == NULL) {
                    fprintf(stderr, "\nError opening file for reading.\n");
                    return 1;
                }
                root = deserializeTree(fp);
                fclose(fp);
                printTree(root, 0);
                printf("\n");
                system("pause");
                break;
            
            case 13:
                printf("Enter two keys to find LCA: ");
                int n1, n2;
                scanf("%d %d", &n1, &n2);
                struct Node* lca = findLCA(root, n1, n2);
                if (lca != NULL)
                    printf("Lowest Common Ancestor of %d and %d: %d\n", n1, n2, lca->data);
                else
                    printf("One or both keys not present in the tree.\n");
                system("pause");
                break;
            
            case 14:
                pruneTree(&root);
                break;
            
            case 15:
                printTree(root, 0);
                printf("\n");
                system("pause");
                break;
            
            default:
                printf("\nInvalid choice. Please enter a valid choice.");
                break;
        }
    } while (choice != 0);
    return 0;
}