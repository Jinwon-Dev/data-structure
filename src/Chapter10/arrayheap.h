#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct HeapNodeType {
    int data;
} HeapNode;

typedef struct ArrayHeapType {
    int maxCount; // 최대 노드 개수
    int currentCount; // 현재 노드 개수
    HeapNode *pData; // 노드 저장을 위한 1차원 array
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap *createArrayMaxHeap(int maxCount);

int insertMaxHeapAH(ArrayMaxHeap *pHeap, int value);

HeapNode *deleteMaxHeapAH(ArrayMaxHeap *pHeap);

void deleteArrayMaxHeap(ArrayMaxHeap *pHeap);

void displayArrayHeap(ArrayMaxHeap *pHeap);

#endif
