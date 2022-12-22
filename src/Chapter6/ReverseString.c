#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedstack.h"

char *reverseString(char *pSource) {
    char *pReturn = NULL;
    int i = 0, size = 0;
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if (pStack != NULL) {
        while (pSource[size] != '\0') {
            pushLS(pStack, pSource[size]);
            size++;
        }

        pReturn = (char *) malloc(sizeof(char) * (size + 1));
        memset(pReturn, 0, sizeof(char) * (size + 1));

        while (i < size) {
            pNode = popLS(pStack);
            if (pNode != NULL) {
                pReturn[i] = pNode->data;
                free(pNode);
            }
            i++;
        }
        deleteLinkedStack(pStack);
    }

    return pReturn;
}

int main(int argc, const char *argv[]) {
    char szSource[] = "ABCD";
    char *pszReverse = reverseString(szSource);
    if (pszReverse != NULL) {
        printf("[%s] => [%s]\n", szSource, pszReverse);

        free(pszReverse);
    }
    return 0;
}
