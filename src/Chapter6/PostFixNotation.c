#include <stdio.h>
#include <stdlib.h>
#include "exprlinkedstack.h"

void calcExpr(ExprToken *pExprTokens, int tokenCount) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode1 = NULL, *pNode2 = NULL;
    Precedence tokenType;
    int i = 0;
    if (pExprTokens == NULL) {
        return;
    }

    pStack = createLinkedStack();
    if (pStack != NULL) {
        for (i = 0; i < tokenCount; i++) {
            tokenType = pExprTokens[i].type;

            if (tokenType == operand) {
                pushLS(pStack, pExprTokens[i]);
            } else {
                pNode2 = popLS(pStack);
                if (pNode2 != NULL) {
                    pNode1 = popLS(pStack);
                    if (pNode1 != NULL) {
                        double op1 = pNode1->data.value;
                        double op2 = pNode2->data.value;

                        ExprToken newToken;
                        newToken.type = operand;
                        switch (tokenType) {
                            case plus:
                                newToken.value = op1 + op2;
                                break;
                            case minus:
                                newToken.value = op1 - op2;
                                break;
                            case multiply:
                                newToken.value = op1 * op2;
                                break;
                            case divide:
                                newToken.value = op1 / op2;
                                break;
                        }
                        pushLS(pStack, newToken);
                        free(pNode1);
                    }
                    free(pNode2);
                }
            }
        }

        pNode1 = popLS(pStack);
        if (pNode1 != NULL) {
            printf("수식 계산 결과는 [%f]입니다\n",
                   pNode1->data.value);
            free(pNode1);
        } else {
            printf("오류,수식에 오류가 있습니다\n");
        }
        deleteLinkedStack(pStack);
    }
}

int main(int argc, const char *argv[]) {

    ExprToken *pExprTokens = (ExprToken *) malloc(sizeof(ExprToken) * 7);
    pExprTokens[0].type = operand;
    pExprTokens[0].value = 2;
    pExprTokens[1].type = operand;
    pExprTokens[1].value = 3;
    pExprTokens[2].type = operand;
    pExprTokens[2].value = 4;
    pExprTokens[3].type = plus;
    pExprTokens[3].value = 0;
    pExprTokens[4].type = operand;
    pExprTokens[4].value = 5;
    pExprTokens[5].type = multiply;
    pExprTokens[5].value = 0;
    pExprTokens[6].type = minus;
    pExprTokens[6].value = 0;

    printf("Expression: 2 3 4 + 5 * -\n");
    calcExpr(pExprTokens, 7);

    free(pExprTokens);

    return 0;
}
