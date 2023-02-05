#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

typedef struct LinkedQueueNodeType {
    int data;
    struct LinkedQueueNodeType *pLink;
} LinkedQueueNode;

typedef struct LinkedQueueType {
    int currentCount;           // 현재 노드의 개수
    LinkedQueueNode *pFront;    // Front 노드의 포인터
    LinkedQueueNode *pRear;     // Rear 노드의 포인터
} LinkedQueue;

LinkedQueue *createLinkedQueue();

int enqueueLQ(LinkedQueue *pQueue, int data);

LinkedQueueNode *dequeueLQ(LinkedQueue *pQueue);

LinkedQueueNode *peekLQ(LinkedQueue *pQueue);

void deleteLinkedQueue(LinkedQueue *pQueue);

int isLinkedQueueEmpty(LinkedQueue *pQueue);

void displayLinkedQueue(LinkedQueue *pQueue);

#endif
