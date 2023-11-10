#include<stdio.h>
#include<stdlib.h>

void insertarr(int arr[], int *size, int position, int element) {
    if(*size >= 100) {
        printf("\nArray is Full. Cannot insert more elements.");
        return;
    }

    if(position < 0 || position > *size) {
        printf("\nInvalid position for insertion.");
        return;
    }

    //Shift element to make space for new arr
    for(int i = *size; i > position; i--) {
        arr[i] = arr[i-1];
    }

    //insert the new element
    arr[position] = element;
    (*size)++;

    printf("\nElement %d inserted at Position %d.\n", element, position);
}

void updatearr(int arr[], int size, int position, int newElement) {
    if(position < 0 || position >= size) {
        printf("\nInvalid position for updating.");
        return;
    }

    arr[position] = newElement;
}

void deletearr(int arr[], int *size, int position) {
    if(position < 0 || position >= *size) {
        printf("\nInvalid position for deletion.\n");
        return;
    }

    for(int i=position; i < *size-1; i++) {
        arr[i] = arr[i+1];
    }
    (*size)--;
}

void printArray(int arr[], int size) {
    printf("Array: ");
    for(int i=0; i<size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[100];
    int size = 0;
    int choice, position, element, newPosition;    

    do {
        system("cls");
        printArray(arr, size);
        printf("\n1. Insertion");
        printf("\n2. Updation");
        printf("\n3. Deletion");
        printf("\n4. Print Array");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the position and arr to insert: ");
            scanf("%d %d", &position, &element);
            insertarr(arr, &size, position-1, element);
            break;

        case 2:
            printf("Enter the position and new element to udpate: ");
            scanf("%d %d", &position, &element);
            updatearr(arr, size, position-1, element);
            break;

        case 3:
            printf("Enter the position to delete: ");
            scanf("%d", &position);
            deletearr(arr, &size, position-1);
            break;

        case 4:
            printArray(arr, size);
            system("pause");
            break;
        
        default:
            printf("Invalid Choice!");
            break;
        }
    }while(choice != 5);
    




    return 0;
}
/*
Array: nD

1D: row
2D: rows, cols

*/