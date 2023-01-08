#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"

BinTree *createExampleBinTree();

void preorderTraversalRecursiveBinTree(BinTree *pBinTree);

void inorderTraversalRecursiveBinTree(BinTree *pBinTree);

void postorderTraversalRecursiveBinTree(BinTree *pBinTree);

int main(int argc, char *argv[]) {
    BinTree *pBinTree = createExampleBinTree();
    if (pBinTree != NULL) {
        printf("전위 순회 결과: ");
        preorderTraversalRecursiveBinTree(pBinTree);
        printf("중위 순회 결과: ");
        inorderTraversalRecursiveBinTree(pBinTree);
        printf("후위 순회 결과: ");
        postorderTraversalRecursiveBinTree(pBinTree);

        deleteBinTree(pBinTree);
    }

    return 0;
}

BinTree *createExampleBinTree() {
    BinTree *pReturn = NULL;
    BinTreeNode *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;

    pReturn = makeBinTree('A');
    if (pReturn != NULL) {
        pNodeA = getRootNodeBT(pReturn);
        pNodeB = addLeftChildNodeBT(pNodeA, 'B');
        pNodeC = addRightChildNodeBT(pNodeA, 'C');
        if (pNodeB != NULL) {
            addLeftChildNodeBT(pNodeB, 'D');
            addRightChildNodeBT(pNodeB, 'E');
        }
        if (pNodeC != NULL) {
            addLeftChildNodeBT(pNodeC, 'F');
            addRightChildNodeBT(pNodeC, 'G');
        }
    }

    return pReturn;
}


void preorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode) {
    if (pNode != NULL) {
        printf("%c ", pNode->data); // V
        preorderTraversalRecursiveBinTreeNode(pNode->pLeftChild); // L
        preorderTraversalRecursiveBinTreeNode(pNode->pRightChild); // R
    }
}

void preorderTraversalRecursiveBinTree(BinTree *pBinTree) {
    if (pBinTree != NULL) {
        preorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

void inorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode) {
    if (pNode != NULL) {
        inorderTraversalRecursiveBinTreeNode(pNode->pLeftChild); // L
        printf("%c ", pNode->data); // V
        inorderTraversalRecursiveBinTreeNode(pNode->pRightChild); // R
    }
}

void inorderTraversalRecursiveBinTree(BinTree *pBinTree) {
    if (pBinTree != NULL) {
        inorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

void postorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode) {
    if (pNode != NULL) {
        postorderTraversalRecursiveBinTreeNode(pNode->pLeftChild); // L
        postorderTraversalRecursiveBinTreeNode(pNode->pRightChild); // R
        printf("%c ", pNode->data); // V

    }
}

void postorderTraversalRecursiveBinTree(BinTree *pBinTree) {
    if (pBinTree != NULL) {
        postorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}
