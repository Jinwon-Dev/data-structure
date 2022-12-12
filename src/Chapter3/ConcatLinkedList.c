#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType {
    int data;
    struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType {
    int currentCount;
    LinkedListNode headerNode;
} LinkedList;

LinkedList *createLinkedList() {
    LinkedList *pReturn = (LinkedList *) malloc(sizeof(LinkedList));
    memset(pReturn, 0, sizeof(LinkedList));
    return pReturn;
}

int getLinkedListData(LinkedList *pList, int position) {
    int i = 0;

    LinkedListNode *pCurrentNode = &(pList->headerNode);
    for (i = 0; i <= position; i++) {
        pCurrentNode = pCurrentNode->pLink;
    }

    return pCurrentNode->data;
}

int addLinkedListData(LinkedList *pList, int position, int data) {
    int i = 0;
    LinkedListNode *pNewNode = NULL;
    LinkedListNode *pPreNode = NULL;

    pNewNode = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    pNewNode->data = data;

    pPreNode = &(pList->headerNode);
    for (i = 0; i < position; i++) {
        pPreNode = pPreNode->pLink;
    }

    pNewNode->pLink = pPreNode->pLink;
    pPreNode->pLink = pNewNode;
    pList->currentCount++;
    return 0;
}

int removeLinkedListData(LinkedList *pList, int position) {
    int i = 0;
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = NULL;

    pPreNode = &(pList->headerNode);
    for (i = 0; i < position; i++) {
        pPreNode = pPreNode->pLink;
    }

    pDelNode = pPreNode->pLink;
    pPreNode->pLink = pDelNode->pLink;
    free(pDelNode);
    pList->currentCount--;
    return 0;
}

void deleteLinkedList(LinkedList *pList) {
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = pList->headerNode.pLink;
    while (pPreNode != NULL) {
        pDelNode = pPreNode;
        pPreNode = pPreNode->pLink;

        free(pDelNode);
    }

    free(pList);
}

int getLinkedListLength(LinkedList *pList) {
    if (NULL != pList) {
        return pList->currentCount;
    }
    return 0;
}

void iterateLinkedList(LinkedList *pList) {
    int count = 0;
    LinkedListNode *pNode = NULL;

    pNode = pList->headerNode.pLink;
    while (pNode != NULL) {
        printf("[%d],%d\n", count, pNode->data);
        count++;

        pNode = pNode->pLink;
    }
    printf("노드 개수: %d\n", count);
}

void concatLinkedList(LinkedList *pListA, LinkedList *pListB) {
    LinkedListNode *pNodeA = NULL; // 연결 리스트 pListA의 마지막 노드를 가리킬 pNodeA

    if (pListA != NULL && pListB != NULL) { // 입력 파라미터 유효성 점검
        pNodeA = pListA->headerNode.pLink; // 노드 pNodeA가 연결 리스트 pListA의 첫 번째 노드를 가리키게 한다(헤더 노드의 다음 노드)

        while (pNodeA != NULL && pNodeA->pLink != NULL) { // pNodeA가 마지막 노드를 가리킬 때까지 루프를 돈다
            pNodeA = pNodeA->pLink;
        }
        pNodeA->pLink = pListB->headerNode.pLink; // pNodeA의 다음 노드로 pListB의 첫 번째 노드를 설정한다

        pListB->headerNode.pLink = NULL; // 연결 리스트 pListB는 빈 연결 리스트가 되도록 한다
    }
}

int main(int argc, char *argv[]) {
    LinkedList *pListA = NULL; // 연결 리스트 pListA 선언
    LinkedList *pListB = NULL; // 연결 리스트 pListB 선언

    pListA = createLinkedList(); // 연결 리스트 pListA 생성
    pListB = createLinkedList(); // 연결 리스트 pListB 생성
    addLinkedListData(pListA, 0, 10); // 연결 리스트 pListA에 자료 10 추가
    addLinkedListData(pListA, 1, 20); // 연결 리스트 pListA에 자료 20 추가
    addLinkedListData(pListA, 2, 30); // 연결 리스트 pListA에 자료 30 추가
    addLinkedListData(pListB, 0, 40); // 연결 리스트 pListB에 자료 40 추가
    addLinkedListData(pListB, 1, 50); // 연결 리스트 pListB에 자료 50 추가

    printf("연결 리스트 결합 전\n");
    printf("\n연결 리스트 A\n");
    iterateLinkedList(pListA);
    printf("\n연결 리스트 B\n");
    iterateLinkedList(pListB);

    concatLinkedList(pListA, pListB);

    printf("\n연결 리스트 결합 후\n");
    printf("\n연결 리스트 A\n");
    iterateLinkedList(pListA);
    printf("\n연결 리스트 B\n");
    iterateLinkedList(pListB);


    deleteLinkedList(pListA);
    deleteLinkedList(pListB);

    return 0;
}