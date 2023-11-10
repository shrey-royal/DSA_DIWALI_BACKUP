#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* getNewNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(!newNode) {
        printf("\nMemory allocation Failed.");
        return NULL;
    }
    return newNode;
}

void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = getNewNode();

    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = getNewNode();
    newNode->data = value;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtPosition(struct Node** head, int value, int position) {
    if(position < 1) {
        printf("\nInvalid Position. Please enter a position greater than 0.");
        return;
    }

    if(position == 1) {
        insertAtBeginning(head, value);
        return;
    }

    struct Node* newNode = getNewNode();
    newNode->data = value;

    struct Node* temp = *head;
    for(int i=0; i<position-1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("\nPosition out of range. Cannot insert at the specified Position.");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void searchByValue(struct Node* head, int key) {
    struct Node* temp = head;
    int position = 1;
    while(temp != NULL) {
        if(temp->data == key) {
            printf("\nValue %d found at position %d.", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }

    printf("\nValue %d not found in the list.", key);
}

int getLength(struct Node* head) {
    int length = 0;
    struct Node* temp = head;
    while(temp != NULL) {
        length++;
        temp = temp->next;
    }

    return length;
}

void reverseList(struct Node** head) {
    struct Node *prev, *current, *next;
    prev = NULL;
    current = *head;

    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void deleteAtBeginning(struct Node** head) {
    if(*head == NULL) {
        printf("\nList is empty. Cannot delete from an empty list.");
        return;
    }

    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteAtEnd(struct Node** head) {
    if(*head == NULL) {
        printf("\nList is empty. Cannot delete from an empty list.");
        return;
    }

    if((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    struct Node* temp = *head;
    while(temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
}

void deleteAtPosition(struct Node** head, int position) {
    if(*head == NULL) {
        printf("\nList is empty. Cannot delete from an empty list.");
        return;
    }

    if(position < 1) {
        printf("\nInvalid position. Please enter a position greater than 0.");
        return;
    }

    if(position == 1) {
        deleteAtBeginning(head);
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;

    for (int i = 1; i < position && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("\nPosition out of range. Cannot delete at the specified position.");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void printListFromBeginning(struct Node* head) {
    if(head == NULL) {
        printf("\nList is Empty!");
        return;
    }

    struct Node* temp = head;

    printf("\nList: ");
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void printListFromEnd(struct Node* head) {
    if(head == NULL) {
        return;
    }

    printListFromEnd(head->next);
    printf("%d, ", head->data);
}

void freeList(struct Node** head) {
    struct Node* temp;
    while(*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}


int main() {
    struct Node* head = NULL;
    int choice, value, position;

    do{
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

        switch (choice) {
            case 1:
                printf("\nEnter the value to insert at front: ");
                scanf("%d", &value);
                insertAtBeginning(&head, value);
                break;

            case 2:
                printf("\nEnter the value to insert at end: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;

            case 3:
                printf("\nEnter the position to insert the data at: ");
                scanf("%d", &position);
                printf("\nEnter the value to insert at %d position: ", position);
                scanf("%d", &value);
                insertAtPosition(&head, value, position-1);
                break;

            case 4:
                printf("\nEnter the value that you want to search from the list: ");
                scanf("%d", &value);
                searchByValue(head, value);
                printf("\n");
                system("pause");
                break;

            case 5:
                printf("\nThe Current length of the list is %d.\n", getLength(head));
                system("pause");
                break;

            case 6:
                reverseList(&head);
                break;

            case 7:
                deleteAtBeginning(&head);
                break;

            case 8:
                deleteAtEnd(&head);
                break;

            case 9:
                printf("\nEnter the position that you want to delete the element from: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;

            case 10:
                printListFromBeginning(head);
                printf("\n");
                system("pause");    //press any key to continue...
                break;

            case 11:
                printf("\nList from end: ");
                printListFromEnd(head);
                break;

            case 0:
                freeList(&head);
                printf("\nExiting the Program. GoodBye!");
                printListFromBeginning(head);
                printf("\n");
                system("pause");
                break;
        
            default:
                printf("\nInvalid Choice. Please try again!");
                break;
        }
    }while (choice != 0);

    return 0;
}
/*
LinkedList: it is a way storing data with the address of the next memory where the data is located. 

Operations:
    1. insertatbeginning
    2. insertatend
    3. insertatposition
    4. searchbyvalue
    5. length
    6. reverseList
    7. deleteatbeginning
    8. deleteatend
    9. deleteatposition
    10. printlistfrombeginning
    11. printlistfromend
    12. freelist

*/