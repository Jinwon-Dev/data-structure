#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedStackNodeType {
    char data;
    struct LinkedStackNodeType *pLink;
} LinkedStackNode;

typedef struct LinkedStackType {
    int currentCount;       // 현재 원소의 개수
    LinkedStackNode *pTop;    // Top 노드의 포인터
} LinkedStack;


LinkedStack *createLinkedStack() {
    LinkedStack *pReturn = NULL;
    pReturn = (LinkedStack *) malloc(sizeof(LinkedStack));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(LinkedStack));
    } else {
        printf("오류, 메모리할당,createLinkedStack()\n");
        return NULL;
    }

    return pReturn;
}

int pushLS(LinkedStack *pStack, char data) {
    int ret = 0;
    LinkedStackNode *pNode = NULL;

    if (pStack != NULL) {
        pNode = (LinkedStackNode *) malloc(sizeof(LinkedStackNode)); // Step-A: 새로운 노드를 생성하고 자료를 지정
        if (pNode != NULL) {
            pNode->data = data;
            pNode->pLink = pStack->pTop; // Step-B: 새로 추가한 노드의 이전 노드로 기존 탑 노드를 지정
            pStack->pTop = pNode; // Step-C: 연결 스택의 탑 노드를 새로 추가한 노드로 변경

            pStack->currentCount++;
            ret = 1;
        } else {
            printf("오류, 메모리할당,pushLS()\n");
        }
    }

    return ret;
}

int isLinkedStackEmpty(LinkedStack *pStack) {
    int ret = 0;

    if (pStack != NULL) {
        if (pStack->currentCount == 0) {
            ret = 1;
        }
    }

    return ret;
}

LinkedStackNode *popLS(LinkedStack *pStack) {
    LinkedStackNode *pReturn = NULL;
    if (pStack != NULL) {
        if (isLinkedStackEmpty(pStack) == 0) { // 유효성 점검, 연결 스택이 비어있는지 점검
            pReturn = pStack->pTop; // Step-A: 기존 탑 노드를 반환 노드로 지정
            pStack->pTop = pReturn->pLink; // Step-B: 새로운 탑 노드를 기존 탑 노드의 이전 노드로 지정
            pReturn->pLink = NULL; // Step-C: 반환 노드의 이전 노드 정보를 초기화

            pStack->currentCount--; // 연결 스택의 노드 개수를 1 감소
        }
    }

    return pReturn;
}

LinkedStackNode *peekLS(LinkedStack *pStack) {
    LinkedStackNode *pReturn = NULL;
    if (pStack != NULL) {
        if (isLinkedStackEmpty(pStack) == 0) { // 유효성 점검, 연결 스택이 비어 있는지 점검
            pReturn = pStack->pTop; // 반환 값 지정, 스택의 탑 노드를 가리키는 포인터 반환
        }
    }

    return pReturn;
}

void deleteLinkedStack(LinkedStack *pStack) {
    LinkedStackNode *pNode = NULL;
    LinkedStackNode *pDelNode = NULL;

    if (pStack != NULL) {
        pNode = pStack->pTop;
        while (pNode != NULL) {
            pDelNode = pNode;
            pNode = pNode->pLink;
            free(pDelNode);
        }
        free(pStack);
    }
}

void displayLinkedStack(LinkedStack *pStack) {
    LinkedStackNode *pNode = NULL;
    int i = 1;
    if (pStack != NULL) {
        printf("현재 노드 개수: %d\n",
               pStack->currentCount);
        pNode = pStack->pTop;
        while (pNode != NULL) {
            printf("[%d]-[%c]\n",
                   pStack->currentCount - i,
                   pNode->data);
            i++;
            pNode = pNode->pLink;
        }
    }
}

int main(int argc, char *argv[]) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if (pStack != NULL) {
        pushLS(pStack, 'A');
        pushLS(pStack, 'B');
        pushLS(pStack, 'C');
        pushLS(pStack, 'D');
        displayLinkedStack(pStack);

        pNode = popLS(pStack);
        if (pNode != NULL) {
            printf("Pop-[%c]\n", pNode->data);
            free(pNode);
        }
        displayLinkedStack(pStack);

        pNode = peekLS(pStack);
        if (pNode != NULL) {
            printf("Peek-[%c]\n", pNode->data);
        }
        displayLinkedStack(pStack);

        deleteLinkedStack(pStack);
    }
    return 0;
}
