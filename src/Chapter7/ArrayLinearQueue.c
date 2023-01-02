#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayQueueNodeType {
    char data;
} ArrayQueueNode;

typedef struct ArrayQueueType {
    int maxCount; // 최대 원소 개수
    int currentCount; // 현재 원소의 개수
    int front; // front 위치
    int rear; // rear 위치
    ArrayQueueNode *pData; // 노드 저장을 위한 1차원 배열 포인터
} ArrayQueue;

int isArrayQueueFull(ArrayQueue *pQueue);

int isArrayQueueEmpty(ArrayQueue *pQueue);

ArrayQueue *createArrayQueue(int size) {
    ArrayQueue *pReturn = NULL;

    pReturn = (ArrayQueue *) malloc(sizeof(ArrayQueue)); // 메모리 할당과 0으로 초기화
    memset(pReturn, 0, sizeof(ArrayQueue));
    pReturn->maxCount = size; // 큐 크기 설정
    pReturn->front = -1; // 프런트와 리어의 위치 초기화
    pReturn->rear = -1;

    pReturn->pData = (ArrayQueueNode *) malloc(sizeof(ArrayQueueNode) * size); // 자료를 저장하는 배열의 메모리를 할당
    memset(pReturn->pData, 0, sizeof(ArrayQueueNode) * size);

    return pReturn;
}

int enqueueAQ(ArrayQueue *pQueue, char data) {
    int ret = 0;

    if (pQueue != NULL) { // 입력 파라미터에 대한 유효성 점검, 메모리 NULL 여부 점검
        if (isArrayQueueFull(pQueue) == 0) { // 새로운 자료 추가 가능 여부를 점검
            pQueue->rear++; // 리어 위치 변경
            pQueue->pData[pQueue->rear].data = data; // 새로운 자료 추가
            pQueue->currentCount++; // 현재 자료 개수 증가
            ret = 1;
        } else {
            printf("오류, 큐가 가득 찼습니다, enqueueAQ()\n");
        }
    }

    return ret;
}

int isArrayQueueFull(ArrayQueue *pQueue) {
    int ret = 0;

    if (pQueue != NULL) {
        if (pQueue->currentCount == pQueue->maxCount || pQueue->rear == pQueue->maxCount - 1) {
            ret = 1;
        }
    }

    return ret;
}

ArrayQueueNode *dequeueAQ(ArrayQueue *pQueue) {

    ArrayQueueNode *pReturn = NULL;
    if (pQueue != NULL) { // 입력 파라미터에 대한 유효성 점검, 메모리 NULL 여부와 빈 큐인지 여부
        if (isArrayQueueEmpty(pQueue) == 0) {
            pReturn = (ArrayQueueNode *) malloc(sizeof(ArrayQueueNode)); // 반환 노드에 대한 메모리 할당과 점검
            if (pReturn != NULL) {
                pQueue->front++; // 프런트 위치 변경
                pReturn->data = pQueue->pData[pQueue->front].data; // 반환 노드 내용 복사
                pQueue->currentCount--;
            } else {
                printf("오류,메모리할당,dequeueAQ()\n");
            }
        }
    }

    return pReturn;
}

ArrayQueueNode *peekAQ(ArrayQueue *pQueue) {
    ArrayQueueNode *pReturn = NULL;
    if (pQueue != NULL) {
        if (isArrayQueueEmpty(pQueue) == 0) {
            pReturn = &(pQueue->pData[pQueue->front + 1]);
        }
    }

    return pReturn;
}


int isArrayQueueEmpty(ArrayQueue *pQueue) {
    int ret = 0;

    if (pQueue != NULL) {
        if (pQueue->currentCount == 0) {
            ret = 1;
        }
    }

    return ret;
}

void deleteArrayQueue(ArrayQueue *pQueue) {
    if (pQueue != NULL) {
        if (pQueue->pData != NULL) {
            free(pQueue->pData);
        }
        free(pQueue);
    }
}

void displayArrayQueue(ArrayQueue *pQueue) {
    int i = 0;

    if (pQueue != NULL) {
        printf("큐의 크기: %d, 현재 노드 개수: %d\n",
               pQueue->maxCount,
               pQueue->currentCount);

        for (i = pQueue->front + 1; i <= pQueue->rear; i++) {
            printf("[%d]-[%c]\n", i, pQueue->pData[i].data);
        }
    }
}

int main(int argc, char *argv[]) {
    ArrayQueue *pQueue = NULL;
    ArrayQueueNode *pNode = NULL;

    pQueue = createArrayQueue(4);
    if (pQueue != NULL) {
        // 큐 초기화: 'A', 'B', 'C', 'D' 추가.
        enqueueAQ(pQueue, 'A');
        enqueueAQ(pQueue, 'B');
        enqueueAQ(pQueue, 'C');
        enqueueAQ(pQueue, 'D');
        displayArrayQueue(pQueue);

        pNode = dequeueAQ(pQueue);
        if (pNode != NULL) {
            printf("Dequeue Value-[%c]\n",
                   pNode->data);
            free(pNode);
        }
        displayArrayQueue(pQueue);

        pNode = peekAQ(pQueue);
        if (pNode != NULL) {
            printf("Peek Value-[%c]\n",
                   pNode->data);
        }
        displayArrayQueue(pQueue);

        enqueueAQ(pQueue, 'E');
        displayArrayQueue(pQueue);
    }
    return 0;
}
