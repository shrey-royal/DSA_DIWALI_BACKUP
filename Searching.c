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

void linearSearch(int arr[], int size, int element) {
    int flag=0, i;
    for (i = 0; i < size; i++)
    {
        if(arr[i] == element) {
            printf("%d found at %d position in the array.", element, i+1);
            flag = 1;
        }
    }

    if(!flag) {
        printf("\nElement %d not found in the array.\ni = %d", element, i);
    }
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

void binarySearch(int arr[], int size, int element) {
    bubbleSort(arr, size);
    printArray(arr, size);
    int low = 0, high = size-1, mid=0;
    
    while(low <= high) {
        mid = (low + high) / 2;
        if(arr[mid] == element) {
            printf("\n%d found at %d position in the array.", element, mid+1);
            return;
        } else if(arr[mid] < element) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("\nElement %d not found in the array.", element);
}

int main() {
    //1. linear search, 2. Binary Searchss
    int arr[10] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64}, size = 10;

    // for (int i = 0; i < size; i++) {
    //     arr[i] = rand() % 100;
    // }

    // printArray(arr, size);
    // linearSearch(arr, size, 340);
    binarySearch(arr, size, 34);

    return 0;
}