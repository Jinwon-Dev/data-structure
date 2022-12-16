#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoublyListNodeType {
    int data;
    struct DoublyListNodeType *pLLink; // 왼쪽(이전) 노드
    struct DoublyListNodeType *pRLink; // 오른쪽(다음) 노드, 단순 연결 리스트의 pLink
} DoublyListNode;

typedef struct DoublyListType {
    int currentCount; // 현재 저장된 노드의 개수
    DoublyListNode headerNode; // 헤더 노드
} DoublyList;

DoublyList *createDoublyList() {
    DoublyList *pReturn = (DoublyList *) malloc(sizeof(DoublyList));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(DoublyList));

        pReturn->headerNode.pLLink = &(pReturn->headerNode);
        pReturn->headerNode.pRLink = &(pReturn->headerNode);
    }

    return pReturn;
}

int getDoublyListData(DoublyList *pList, int position) {
    int i = 0;
    DoublyListNode *pCurrentNode = &(pList->headerNode);
    for (int i = 0; i <= position; i++) {
        pCurrentNode = pCurrentNode->pRLink;
    }
    return pCurrentNode->data;
}

int addDoublyListData(DoublyList *pList, int position, int data) {
    int ret = 0, i = 0;
    DoublyListNode *pPreNode = NULL, *pNewNode = NULL;
    pNewNode = (DoublyListNode *) malloc(sizeof(DoublyListNode));
    if (pNewNode != NULL) {
        memset(pNewNode, 0, sizeof(DoublyListNode));
        pNewNode->data = data;

        pPreNode = &(pList->headerNode);
        for (int i = 0; i < position; i++) {
            pPreNode = pPreNode->pRLink;
        }

        pNewNode->pRLink = pPreNode->pRLink;
        pNewNode->pLLink = pPreNode;
        pPreNode->pRLink = pNewNode; // Step-C (1): 이전 노드 처리
        pNewNode->pRLink->pLLink = pNewNode; // Step-C (2): 다음 노드 처리

        pList->currentCount++;
    } else {
        printf("오류, 메모리 할당 addListData()\n");
        return 1;
    }

    return ret;
}

int removeDoublyListData(DoublyList *pList, int position) {
    int ret = 0, i = 0;
    DoublyListNode *pPreNode = NULL, *pDelNode = NULL;

    pPreNode = &(pList->headerNode);
    for (int i = 0; i < position; i++) {
        pPreNode = pPreNode->pRLink;
    }

    pDelNode = pPreNode->pRLink;
    pPreNode->pRLink = pDelNode->pRLink;
    pDelNode->pRLink->pLLink = pPreNode;

    free(pDelNode);
    pList->currentCount--;

    return ret;
}

int getDoublyListLength(DoublyList *pList) {
    int ret = 0;
    if (pList != NULL) {
        ret = pList->currentCount;
    }
    return ret;
}

void displayDoublyList(DoublyList *pList) {
    int i = 0;
    DoublyListNode *pNode = NULL;
    pNode = pList->headerNode.pRLink;
    if (0 == pList->currentCount) {
        printf("자료가 없습니다\n");
    } else {
        printf("노드 개수: %d\n", pList->currentCount);

        for (i = 0; i < pList->currentCount; i++) {
            printf("[%d],%d\n", i, pNode->data);
            pNode = pNode->pRLink;
        }
    }
}

void deleteDoublyList(DoublyList *pList) {
    if (pList != NULL) {
        while (pList->currentCount > 0) {
            removeDoublyListData(pList, 0);
        }
        free(pList);
    }
}

int main(int argc, char *argv[]) {
    DoublyList *pList = pList = createDoublyList();

    if (pList != NULL) {
        addDoublyListData(pList, 0, 10);
        addDoublyListData(pList, 1, 20);
        addDoublyListData(pList, 1, 30);
        displayDoublyList(pList);

        removeDoublyListData(pList, 0);
        displayDoublyList(pList);

        deleteDoublyList(pList);
    }

    return 0;
}