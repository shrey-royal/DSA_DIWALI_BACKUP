#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* prev;
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
    newNode->prev = NULL;
    newNode->next = *head;

    if(*head != NULL) (*head)->prev = newNode;
    *head = newNode;
}

void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = getNewNode();

    newNode->data = value;
    newNode->next = NULL;

    if(*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
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
    newNode->prev = temp;
    if(temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

void searchByValue(struct Node* head, int key) {
    struct Node* temp = head;
    int position = 1;
    while(temp != NULL) {
        if(temp->data == key) {
            printf("\nValue %d found at position %d.\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }

    printf("\nValue %d not found in the list.\n", key);
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
    struct Node* temp = NULL;
    struct Node* current = *head;

    while(current != NULL) {
        temp = current->prev;           //temp = a
        current->prev = current->next;  //a = b
        current->next = temp;           //b = temp
        current = current->prev;        //b++;
    }

    if(temp != NULL) {
        *head = temp->prev;
    }
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
    while(temp->next != NULL) {
        temp = temp->next;
    }

    if(temp->prev != NULL) {
        temp->prev->next = NULL;
    }
    free(temp);
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

    for (int i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if(temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    if(temp->next != NULL) {
        temp->next->prev = temp->next;
    }
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
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


void printListFromEnd(struct Node* head) {
    if(head == NULL) {
        return;
    }

    struct Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    while(temp != NULL) {
            printf("%d <->", temp->data);
            temp = temp->prev;
    }
    printf("\n");
}

void freeList(struct Node** head) {
    struct Node* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
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

        switch (choice)
        {
        case 1:
            printf("\nEnter the value to insert at beginning: ");
            scanf("%d", &value);
            insertAtBeginning(&head, value);
            break;

        case 2:
            printf("\nEnter the value to insert at end: ");
            scanf("%d", &value);
            insertAtEnd(&head, value);
            break;

        case 3:
            printf("\nEnter the position: ");
            scanf("%d", &position);
            printf("\nEnter the value to insert at end: ");
            scanf("%d", &value);
            insertAtPosition(&head, value, position);
            break;

        case 4:
            printf("\nEnter the value to search: ");
            scanf("%d", &value);
            searchByValue(head, value);
            system("pause");
            break;

        case 5:
            printf("\nLength of the list: %d\n", getLength(head));
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
            printf("\nEnter the position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(&head, position);
            printf("\nDeleted from position %d.\n", position);
            break;

        case 10:
            printListFromBeginning(head);
            printf("\n");
            system("pause");
            break;

        case 11:
            printListFromEnd(head);
            printf("\n");
            system("pause");
            break;
        
        default:
            freeList(&head);
            printf("\nInvalid Choice. Please try again.");
            printf("\n");
            printListFromBeginning(head);
            system("pause");            
            break;
        }
    }while (choice != 0);
    return 0;
}