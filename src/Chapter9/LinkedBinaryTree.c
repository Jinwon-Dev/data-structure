#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinTreeNodeType {
    char data; // 노드가 저장하는 자료

    struct BinTreeNodeType *pLeftChild; // 왼쪽 자식 노드를 가리키는 포인터 변수
    struct BinTreeNodeType *pRightChild; // 오른쪽 자식 노드를 가리키는 포인터 변수
} BinTreeNode;

typedef struct BinTreeType {
    struct BinTreeNodeType *pRootNode; // 루트 노드를 가리키는 포인터 변수
} BinTree;

BinTreeNode *makeNewNodeBT(char data) {
    BinTreeNode *pReturn = (BinTreeNode *) malloc(sizeof(BinTreeNode));
    if (pReturn != NULL) {
        pReturn->data = data;
        pReturn->pLeftChild = NULL;
        pReturn->pRightChild = NULL;
    }
    return pReturn;
}

BinTree *makeBinTree(char rootNodeData) {
    BinTree *pReturn = NULL;
    pReturn = (BinTree *) malloc(sizeof(BinTree)); // 메모리 할당
    if (pReturn != NULL) { // 검증
        pReturn->pRootNode = makeNewNodeBT(rootNodeData);
        if (pReturn->pRootNode == NULL) {
            free(pReturn);
            pReturn = NULL;
            printf("오류, 메모리 할당(2), makeBinTree()\n");
        }
    } else {
        printf("오류, 메모리 할당(1), makeBinTree()\n");
    }
    return pReturn;
}

BinTreeNode *addLeftChildNodeBT(BinTreeNode *pParentNode, char data) {
    BinTreeNode *pReturn = NULL;
    if (pParentNode != NULL) { // 유효성 점검
        if (pParentNode->pLeftChild == NULL) { // 유효성 점검
            pParentNode->pLeftChild = makeNewNodeBT(data); // 새로운 노드 할당 후 부모 노드의 왼쪽 자식 노드로 설정
        } else {
            printf("오류, 이미 노드가 존재합니다, addLeftChildNodeBT()\n");
        }
    }
    return pReturn;
}

BinTreeNode *addRightChildNodeBT(BinTreeNode *pParentNode, char data) {
    BinTreeNode *pReturn = NULL;
    if (pParentNode != NULL) { // 유효성 점검
        if (pParentNode->pRightChild == NULL) { // 유효성 점검
            pParentNode->pRightChild = makeNewNodeBT(data); // 새로운 노드 할당 후 부모 노드의 오른쪽 자식 노드로 설정
        } else {
            printf("오류, 이미 노드가 존재합니다, addRightChildNodeBT()\n");
        }
    }
    return pReturn;
}

BinTreeNode *getRootNodeBT(BinTree *pBinTree) {
    BinTreeNode *pReturn = NULL;

    if (pBinTree != NULL) {
        pReturn = pBinTree->pRootNode;
    }

    return pReturn;
}

void deleteBinTreeNode(BinTreeNode *pNode) {
    if (pNode != NULL) {
        deleteBinTreeNode(pNode->pLeftChild);
        deleteBinTreeNode(pNode->pRightChild);
        free(pNode);
    }
}

void deleteBinTree(BinTree *pBinTree) {
    if (pBinTree != NULL) {
        deleteBinTreeNode(pBinTree->pRootNode);
        free(pBinTree);
    }
}

int main(int argc, char *argv[]) {
    BinTree *pBinTree = NULL;
    BinTreeNode *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;
    BinTreeNode *pNodeD = NULL, *pNodeE = NULL, *pNodeF = NULL;

    pBinTree = makeBinTree('A');
    if (pBinTree != NULL) {
        pNodeA = getRootNodeBT(pBinTree);
        pNodeB = addLeftChildNodeBT(pNodeA, 'B');
        pNodeC = addRightChildNodeBT(pNodeA, 'C');

        if (pNodeB != NULL) {
            pNodeD = addLeftChildNodeBT(pNodeB, 'D');
        }
        if (pNodeC != NULL) {
            pNodeE = addLeftChildNodeBT(pNodeC, 'E');
            pNodeF = addRightChildNodeBT(pNodeC, 'F');
        }

        deleteBinTree(pBinTree);
    }

    return 0;
}
