#ifndef _LINKEDSTACK_
#define _LINKEDSTACK_

typedef struct LinkedStackNodeType {
    char data;
    struct LinkedStackNodeType *pLink;
} LinkedStackNode;

typedef struct LinkedStackType {
    int currentCount;
    struct LinkedStackNodeType *pTop;
} LinkedStack;

LinkedStack *createLinkedStack();

int pushLS(LinkedStack *pStack, char data);

int isLinkedStackEmpty(LinkedStack *pStack);

LinkedStackNode *popLS(LinkedStack *pStack);

LinkedStackNode *peekLS(LinkedStack *pStack);

void deleteLinkedStack(LinkedStack *pStack);

void displayLinkedStack(LinkedStack *pStack);

#endif
