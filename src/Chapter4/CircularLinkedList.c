#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CircularListNodeType {
    int data;
    struct CircularListNodeType *pLink;
} CircularListNode;

typedef struct CircularListType {
    int currentCount;
    CircularListNode headerNode;
} CircularList;

CircularList *createCircularList() {
    CircularList *pReturn = (CircularList *) malloc(sizeof(CircularList));
    memset(pReturn, 0, sizeof(CircularList));
    return pReturn;
}

int getCircularListData(CircularList *pList, int position) {
    int i = 0;

    CircularListNode *pCurrentNode = &(pList->headerNode);
    for (int i = 0; i <= position; i++) {
        pCurrentNode = pCurrentNode->pLink;
    }

    return pCurrentNode->data;
}

int addCircularListData(CircularList *pList, int position, int data) {
    int i = 0;

    CircularListNode *pNewNode = NULL;
    CircularListNode *pPreNode = NULL;

    pNewNode = (CircularListNode *) malloc(sizeof(CircularListNode));
    pNewNode->data = data;

    pPreNode = &(pList->headerNode);
    for (int i = 0; i < position; i++) {
        pPreNode = pPreNode->pLink;
    }

    pNewNode->pLink = pPreNode->pLink;
    pPreNode->pLink = pNewNode;

    pList->currentCount++;
    if (pNewNode->pLink == NULL) { // 첫 번째 노드가 추가된 경우, 다음 노드를 지정
        pNewNode->pLink = pNewNode;
    }

    return 0;
}

int removeCircularListData(CircularList *pList, int position) {
    int i = 0;
    CircularListNode *pDelNode = NULL;
    CircularListNode *pPreNode = NULL;

    pPreNode = &(pList->headerNode);
    for (int i = 0; i < position; i++) {
        pPreNode = pPreNode->pLink;
    }

    pDelNode = pPreNode->pLink;
    pPreNode->pLink = pDelNode->pLink;

    pList->currentCount--;
    if (0 == pList->currentCount) { // 마지막 남은 노드가 삭제된 경우, 헤더 노드를 NULL로 지정
        pList->headerNode.pLink = NULL;
    }

    free(pDelNode);

    return 0;
}

void deleteCircularList(CircularList *pList) {
    int i = 0;
    CircularListNode *pDelNode = NULL;
    CircularListNode *pPreNode = pList->headerNode.pLink;
    for (int i = 0; i < pList->currentCount; i++) {
        pDelNode = pPreNode;
        pPreNode = pPreNode->pLink;

        free(pDelNode);
    }

    free(pList); // 원형 연결 리스트 자체에 대한 메모리를 해제
}

void displayCircularList(CircularList *pList) {
    int i = 0;
    CircularListNode *pNode = NULL;

    pNode = pList->headerNode.pLink;
    if (0 == pList->currentCount) {
        printf("자료가 없습니다\n");
    } else {
        printf("노드 개수: %d\n", pList->currentCount);

        for (int i = 0; i < pList->currentCount; i++) {
            printf("[%d],%d\n", i, pNode->data);
            pNode = pNode->pLink;
        }
    }
}

int main(int argc, char *argv[]) {
    CircularList *pList = NULL; // 변수를 선언하고 초기화

    pList = createCircularList(); // 리스트를 생성

    addCircularListData(pList, 0, 10);
    displayCircularList(pList);
    addCircularListData(pList, 0, 20);
    displayCircularList(pList);
    addCircularListData(pList, 1, 30);
    displayCircularList(pList);

    removeCircularListData(pList, 2);
    displayCircularList(pList);
    removeCircularListData(pList, 1);
    displayCircularList(pList);
    removeCircularListData(pList, 0);
    displayCircularList(pList);

    deleteCircularList(pList); // 리스트 자체를 삭제

    return 0;
}