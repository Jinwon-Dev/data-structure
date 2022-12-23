#include <stdio.h>
#include <stdlib.h>
#include "exprlinkedstack.h"

int inStackPrecedence(Precedence oper);

int outStackPrecedence(Precedence oper);

void printToken(ExprToken element);

void convertInfixToPostfix(ExprToken *pExprTokens, int tokenCount) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;
    Precedence tokenType, inStackTokenType;
    int i = 0;

    pStack = createLinkedStack();
    if (pStack != NULL) {
        for (i = 0; i < tokenCount; i++) {
            tokenType = pExprTokens[i].type;
            switch (tokenType) {
                case operand:
                    printf("%4.1f\t", pExprTokens[i].value);
                    break;
                case rparen:
                    pNode = popLS(pStack);
                    while (pNode != NULL && pNode->data.type != lparen) {
                        printToken(pNode->data);
                        free(pNode);

                        pNode = popLS(pStack);
                    }
                    if (pNode != NULL) free(pNode);
                    break;
                default:
                    while (isLinkedStackEmpty(pStack) == 0) {
                        inStackTokenType = peekLS(pStack)->data.type;
                        if (outStackPrecedence(tokenType)
                            <= inStackPrecedence(inStackTokenType)) {
                            pNode = popLS(pStack);
                            if (pNode != NULL) {
                                printToken(pNode->data);
                                free(pNode);
                            }
                        } else {
                            break;
                        }
                    }
                    pushLS(pStack, pExprTokens[i]);
                    break;
            }
        }

        while (isLinkedStackEmpty(pStack) == 0) {
            pNode = popLS(pStack);
            if (pNode != NULL) {
                printToken(pNode->data);
                free(pNode);
            }
        }
        deleteLinkedStack(pStack);
    }
}

int inStackPrecedence(Precedence oper) {
    switch (oper) {
        case lparen:
            return 0;
        case rparen:
            return 4;
        case multiply:
        case divide:
            return 2;
        case plus:
        case minus:
            return 1;
    }
    return -1;
}

int outStackPrecedence(Precedence oper) {
    switch (oper) {
        case lparen:
            return 5;
        case rparen:
            return 4;
        case multiply:
        case divide:
            return 2;
        case plus:
        case minus:
            return 1;
    }
    return -1;
}

void printToken(ExprToken element) {
    switch (element.type) {
        case lparen:
            printf("(\t");
            break;
        case rparen:
            printf(")\t");
            break;
        case plus:
            printf("+\t");
            break;
        case minus:
            printf("-\t");
            break;
        case multiply:
            printf("*\t");
            break;
        case divide:
            printf("/\t");
            break;
        case operand:
            printf("%4.1f\t", element.value);
            break;
    }
}


int main(int argc, const char *argv[]) {


    // 2 - (3 + 4 ) * 5
    ExprToken *pExprTokens = (ExprToken *) malloc(sizeof(ExprToken) * 9);
    pExprTokens[0].type = operand;
    pExprTokens[0].value = 2;
    pExprTokens[1].type = minus;
    pExprTokens[1].value = 0;
    pExprTokens[2].type = lparen;
    pExprTokens[2].value = 0;
    pExprTokens[3].type = operand;
    pExprTokens[3].value = 3;
    pExprTokens[4].type = plus;
    pExprTokens[4].value = 0;
    pExprTokens[5].type = operand;
    pExprTokens[5].value = 4;
    pExprTokens[6].type = rparen;
    pExprTokens[6].value = 0;
    pExprTokens[7].type = multiply;
    pExprTokens[7].value = 0;
    pExprTokens[8].type = operand;
    pExprTokens[8].value = 5;

    printf("Infix Expression: 2.0 - (3.0 + 4.0 ) * 5.0\n");
    printf("Postfix Expression: \n");

    convertInfixToPostfix(pExprTokens, 9);

    free(pExprTokens);

    return 0;
}
