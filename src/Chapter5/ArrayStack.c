#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayStackNodeType {
    char data;
} ArrayStackNode;

typedef struct ArrayStackType {
    int maxCount; // 최대 자료 개수
    int currentCount; // 현재 저장된 자료의 개수
    ArrayStackNode *pData; // 자료를 저장하는 1차원 배열
} ArrayStack;

ArrayStack *createArrayStack(int size) {
    ArrayStack *pReturn = NULL;
    pReturn = (ArrayStack *) malloc(sizeof(ArrayStack)); // 메모리 할당
    memset(pReturn, 0, sizeof(ArrayStack)); // 메모리 초기화
    pReturn->maxCount = size; // 최대 자료 개수 지정

    pReturn->pData = (ArrayStackNode *) malloc(sizeof(ArrayStackNode) * size);
    memset(pReturn->pData, 0, sizeof(ArrayStackNode) * size);

    return pReturn;
}

int isArrayStackFull(ArrayStack *pStack) {
    int ret = 0;
    if (pStack != NULL) {
        if (pStack->currentCount == pStack->maxCount) {
            ret = 1;
        }
    }
    return ret;
}

int pushAS(ArrayStack *pStack, char data) {
    int ret = 0;
    if (isArrayStackFull(pStack) == 0) { // 유효성 점검, 배열 스택이 가득 차있는지를 판단
        pStack->pData[pStack->currentCount].data = data; // 실제 자료를 탑에 추가
        pStack->currentCount++; // 탑의 위치를 변경
        ret = 1;
    } else {
        printf("오류, 스택이 가득 찼습니다, pushAS()\n");
    }
    return ret;
}

int isArrayStackEmpty(ArrayStack *pStack) {
    int ret = 0;

    if (pStack != NULL) {
        if (pStack->currentCount == 0) {
            ret = 1;
        }
    }

    return ret;
}

ArrayStackNode *popAS(ArrayStack *pStack) {
    ArrayStackNode *pReturn = NULL;

    if (0 == isArrayStackEmpty(pStack)) { // 유효형 점검, 배열 스택이 비어있는지 점검
        pReturn = (ArrayStackNode *) malloc(sizeof(ArrayStackNode)); // 반환할 노드에 대해 메모리 할당 및 메모리 점검
        if (pReturn != NULL) {
            pReturn->data = pStack->pData[pStack->currentCount - 1].data; // 노드에 반환할 자료를 대입
            pStack->currentCount--; // 배열 스택의 탑 위치 변경, 한 칸 왼쪽으로
        } else {
            printf("오류, 메모리 할당, popAS()\n");
        }
    }

    return pReturn;
}

ArrayStackNode *peekAS(ArrayStack *pStack) {
    ArrayStackNode *pReturn = NULL;
    if (pStack != NULL) {
        if (isArrayStackEmpty(pStack) == 0) { // 유효성 점검, 배열 스택이 비어있는지 점검
            pReturn = &(pStack->pData[pStack->currentCount - 1]); // 반환 값 지정, 배열 스택의 탑 노드를 가리키는 포인터 반환
        }
    }

    return pReturn;
}

void deleteArrayStack(ArrayStack *pStack) {
    if (pStack != NULL) {
        if (pStack->pData != NULL) {
            free(pStack->pData);
        }
        free(pStack);
    }
}

void displayArrayStack(ArrayStack *pStack) {
    int i = 0;
    if (pStack != NULL) {
        int size = pStack->maxCount;
        int top = pStack->currentCount;

        printf("스택 크기: %d, 현재 노드 개수: %d\n",
               pStack->maxCount,
               pStack->currentCount);

        for (i = size - 1; i >= top; i--) {
            printf("[%d]-[Empty]\n", i);
        }

        for (i = top - 1; i >= 0; i--) {
            printf("[%d]-[%c]\n",
                   i, pStack->pData[i].data);
        }
    }
}

int main(int argc, char *argv[]) {
    ArrayStack *pStack = NULL;
    ArrayStackNode *pNode = NULL;

    pStack = createArrayStack(6);
    if (pStack != NULL) {
        pushAS(pStack, 'A');
        pushAS(pStack, 'B');
        pushAS(pStack, 'C');
        pushAS(pStack, 'D');
        displayArrayStack(pStack);

        pNode = popAS(pStack);
        if (pNode != NULL) {
            printf("Pop 값-[%c]\n", pNode->data);
            free(pNode);
        }

        displayArrayStack(pStack);

        pNode = peekAS(pStack);
        if (pNode != NULL) {
            printf("Peek 값-[%c]\n", pNode->data);
        }
        displayArrayStack(pStack);

        deleteArrayStack(pStack);
    }

    return 0;
}