#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

int checkBracketMatching(char *pSource) {
    int ret = 0, i = 0;
    char symbol = '\0', checkSymbol = '\0';
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if (pStack != NULL) {
        while (0 != pSource[i] && 0 == ret) {
            symbol = pSource[i];
            switch (symbol) {
                case '(':
                case '[':
                case '{':
                    pushLS(pStack, symbol);
                    break;
                case ')':
                case ']':
                case '}':
                    pNode = popLS(pStack);
                    if (pNode == NULL) {
                        ret = 1; // 여는 괄호가 부족한 경우.
                    } else {
                        checkSymbol = pNode->data;
                        if ((symbol == ')' && checkSymbol == '(')
                            || (symbol == ']' && checkSymbol == '[')
                            || (symbol == '}' && checkSymbol == '{')) {
                            // 올바른 경우.
                        } else {
                            ret = 2; // 괄호의 쌍이 맞지 않는 경우.
                        }
                        free(pNode);
                    }
                    break;
            }
            i++;
        }

        if (0 == ret && isLinkedStackEmpty(pStack) == 0) {
            ret = 3; // 여는 괄호가 남은 경우.
        }
        deleteLinkedStack(pStack);
    }
    return ret;

}

int main(int argc, const char *argv[]) {
    int checkResult = 0, i = 0;
    char szExpressionStr[][50] = {
            "( A + B ) * C",
            "{ ( A + B ) * C } * D",
            "( A + B ) * C )",
            "( ( A + B ) * C",
            "{ ( A + B } ) * C * D"
    };

    for (i = 0; i < sizeof(szExpressionStr) / sizeof(szExpressionStr[0]); i++) {
        checkResult = checkBracketMatching(szExpressionStr[i]);
        if (checkResult == 0) {
            printf("SUCCESS, %s\n", szExpressionStr[i]);
        } else {
            printf("FAIL-[%d], %s\n", checkResult, szExpressionStr[i]);
        }
    }

    return 0;
}
