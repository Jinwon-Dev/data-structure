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
    memset(pReturn, 0, sizeof(LinkedList)); // 할당된 메모리를 0으로 초기화
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

    pNewNode->pLink = pPreNode->pLink; // 다음 노드의 처리
    pPreNode->pLink = pNewNode; // 이전 노드의 처리
    pList->currentCount++; // 현재 노드 개수 1 증가
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

    pDelNode = pPreNode->pLink; // (전처리) 제거하려는 노드 지정
    pPreNode->pLink = pDelNode->pLink; // Step-A, 이전 노드의 처리
    free(pDelNode); // Step-B, 제거 노드의 메모리 해제
    pList->currentCount--; // 현재 노드 개수 1 감소
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

    free(pList); // 연결 리스트 자체를 메모리 해제시킴
}

int getLinkedListLength(LinkedList *pList) {
    if (NULL != pList) {
        return pList->currentCount;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    LinkedList *pList = NULL;
    int value = 0;

    pList = createLinkedList(); // Step-1. 리스트 생성
    addLinkedListData(pList, 0, 10); // Step-2. 리스트 1번째 위치에 자료 10 저장
    addLinkedListData(pList, 1, 20); // Step-3. 리스트 2번째 위치에 자료 20 저장
    addLinkedListData(pList, 1, 30); // Step-4. 리스트 2번째 위치에 자료 30 저장

    value = getLinkedListData(pList, 1); // Step-5. 리스트의 2번째 자료의 값을 가져 와서 화면에 출력
    printf("위치: %d, 값: %d\n", 1, value);

    removeLinkedListData(pList, 0); // Step-6. 리스트의 1번째 자료를 제거
    deleteLinkedList(pList); // Step-7. 리스트 자체를 삭제

    return 0;
}