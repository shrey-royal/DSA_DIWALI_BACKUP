#include<stdio.h>
#include<stdlib.h>

void printArray(int arr[], int size) {
    printf("\nArray: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size; i++)
    {
        for(int j=0; j<size-1; j++) {
            if(arr[i] < arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size-1; i++) {
        int min_index = i;
        for(int j = i+1; j < size; j++) {
            if(arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(&arr[i], &arr[min_index]);
        // printf("Iteration %d: ", i+1);
        // printArray(arr, size);
    }
}

void insertionSort(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        int key = arr[i];   //extracted element
        int j = i-1;    //sorted array index
        while(j >= 0 && arr[j] > key) {
            arr[j+1]  = arr[j];
            j -= 1;
        }
        arr[j+1] = key;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low-1);
    for (int j = low; j <= high-1; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&pivot, &arr[i+1]);
    return (i+1);
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex-1);
        quickSort(arr, pivotIndex+1, high);
    }
}


int main() {
    int arr[10] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64}, size = 10;

    // for (int i = 0; i < size; i++) {
    //     arr[i] = rand() % 100;
    // }

    printArray(arr, size);

    // bubbleSort(arr, size);
    // selectionSort(arr, size);
    // insertionSort(arr, size);
    quickSort(arr, 0, size-1);

    printArray(arr, size);

    return 0;
}