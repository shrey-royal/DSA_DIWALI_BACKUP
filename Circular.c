#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* getNewNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("\nMemory allocation Failed.");
        return NULL;
    }
    return newNode;
}

struct Node* insertAtBeginning(struct Node* head, int value) {
    struct Node* newNode = getNewNode();

    newNode->data = value;
    newNode->next = newNode;

    if(head == NULL) {
        head = newNode;
        return head;
    }

    struct Node* temp = head;
    while(temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    head = newNode;

    return head;
}

struct Node* insertAtEnd(struct Node* head, int value) {
    struct Node* newNode = getNewNode();
    newNode->data = value;
    newNode->next = newNode;

    if(head == NULL) {
        head = newNode;
        return head;
    }

    struct Node* temp = head;
    while(temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    // head = newNode;

    return head;
}

struct Node* deleteAtBeginning(struct Node* head) {
    if(head == NULL) {
        printf("\nList is Empty. Cannot delete from the front.\n");
        return head;
    }

    struct Node* temp = head;
    while(temp->next != head) {
        temp = temp->next;
    }
    temp->next = head->next;
    free(head);
    head = temp->next;

    return head;
}

void printListFromBeginning(struct Node* head) {
    if (head == NULL) {
        printf("\nList is Empty!");
        return;
    }

    struct Node* temp = head;
    printf("\nList: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf(" (head)\n");
}


int main() {
    struct Node* head = NULL;
    int choice, value, position;
    
    do {
        system("cls");
        printListFromBeginning(head);
        printf("\n\n1. Insert at beginning");
        printf("\n2. Insert at End");
        printf("\n3. Insert at Position");
        printf("\n4. Search By Value");
        printf("\n5. Length of the list");
        printf("\n6. Reverse the List");
        printf("\n7. Delete at beginning");
        printf("\n8. Delete at end");
        printf("\n9. Delete at Position");
        printf("\n10. Print list from beginning");
        printf("\n11. Print list from end");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nEnter a value to insert at front: ");
                scanf("%d", &value);
                head = insertAtBeginning(head, value);
                break;

            case 2:
                printf("\nEnter a value to insert at front: ");
                scanf("%d", &value);
                head = insertAtEnd(head, value);
                break;

            case 7:
                head = deleteAtBeginning(head);
                break;

            case 10:
                printListFromBeginning(head);
                system("pause");
                break;

            default:
                printf("\nInvalid Choice. Please try again!");
                break;
        }
    }while(choice != 0);

    return 0;
}