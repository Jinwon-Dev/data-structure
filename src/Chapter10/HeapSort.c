#include <stdio.h>
#include <stdlib.h>
#include "arrayheap.h"

void printArray(int values[], int count);

// 힙 정렬
void heapSort(int values[], int count) {
    int i = 0;
    ArrayMaxHeap *pHeap = NULL;

    pHeap = createArrayMaxHeap(10);
    if (pHeap != NULL) {
        for (i = 0; i < count; i++) {
            insertMaxHeapAH(pHeap, values[i]);
        }

        for (i = 0; i < count; i++) {
            HeapNode *pNode = deleteMaxHeapAH(pHeap);
            if (pNode != NULL) {
                values[i] = pNode->data;
                free(pNode);
            }
        }

        deleteArrayMaxHeap(pHeap);
    } else {
        printf("오류, createArrayMinHeap() in heapSort()\n");
        return;
    }
}

// 배열 내용 출력
void printArray(int values[], int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int values[] = {10, 50, 70, 80, 60, 20, 40, 30};

    printf("Before Sort\n");
    printArray(values, 8);

    heapSort(values, 8);

    printf("After Sort\n");
    printArray(values, 8);

    return 0;
}
