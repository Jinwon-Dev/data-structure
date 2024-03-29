#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinSearchTreeNodeType {
    int key;
    char value;

    struct BinSearchTreeNodeType *pLeftChild;
    struct BinSearchTreeNodeType *pRightChild;
} BinSearchTreeNode;

typedef struct BinSearchTreeType {
    BinSearchTreeNode *pRootNode;
} BinSearchTree;

BinSearchTree *createBinSearchTree() {
    BinSearchTree *pReturn = NULL;
    pReturn = (BinSearchTree *) malloc(sizeof(BinSearchTree));
    if (pReturn != NULL) {
        pReturn->pRootNode = NULL;
    } else {
        printf("오류, 메모리 할당,createBinSearchTree()\n");
    }

    return pReturn;
}

BinSearchTreeNode *searchBST(BinSearchTree *pBinSearchTree, int key) {
    BinSearchTreeNode *pReturn = NULL;

    if (pBinSearchTree == NULL) { // 이진 검색 트리가 NULL인지 유효성 점검
        return NULL;
    }
    pReturn = pBinSearchTree->pRootNode; // 루트 노드가 시작 노드
    while (pReturn != NULL) { // 종료 조건 조사: 더 남은 노드가 없음
        if (key == pReturn->key) { // 검색 키로 자료를 찾은 경우
            break;
        } else if (key < pReturn->key) { // 검색 키가 현재 키보다 작은 경우
            pReturn = pReturn->pLeftChild;
        } else { // 검색 키가 현재 키보다 큰 경우
            pReturn = pReturn->pRightChild;
        }
    }

    return pReturn;
}

int getParentNode(BinSearchTreeNode *pCurrentNode, int key, BinSearchTreeNode **ppResult) {
    int ret = 1;
    BinSearchTreeNode *pParentNode = NULL;

    while (pCurrentNode != NULL) {
        if (key == pCurrentNode->key) {
            printf("오류,중복된 키-[%d],getParentNode()\n", key);
            ret = 0;
            return ret;
        } else if (key < pCurrentNode->key) {
            pParentNode = pCurrentNode;
            pCurrentNode = pCurrentNode->pLeftChild;
        } else {
            pParentNode = pCurrentNode;
            pCurrentNode = pCurrentNode->pRightChild;
        }
    }
    if (1 == ret) {
        *ppResult = pParentNode;
    }

    return ret;
}


BinSearchTreeNode *createNewBinSearchTreeNode(int key, char value) {
    BinSearchTreeNode *pNewNode = NULL;

    pNewNode = (BinSearchTreeNode *) malloc(sizeof(BinSearchTreeNode));
    if (pNewNode != NULL) {
        pNewNode->key = key;
        pNewNode->value = value;
        pNewNode->pLeftChild = NULL;
        pNewNode->pRightChild = NULL;
    }

    return pNewNode;
}


void insertNewBinSearchTreeNode(BinSearchTree *pBinSearchTree, BinSearchTreeNode *pParentNode, BinSearchTreeNode *pNewNode) {
    if (pParentNode == NULL) {
        pBinSearchTree->pRootNode = pNewNode;
    } else {
        if (pNewNode->key < pParentNode->key) {
            pParentNode->pLeftChild = pNewNode;
        } else {
            pParentNode->pRightChild = pNewNode;
        }
    }
}


int insertDataBST(BinSearchTree *pBinSearchTree, int key, char value) {
    int ret = 1;
    BinSearchTreeNode *pParentNode = NULL;
    BinSearchTreeNode *pNewNode = NULL;

    if (pBinSearchTree == NULL) { // 유효성 점검: NULL이 전달되었는지 점검
        ret = 0;
        return ret;
    }

    ret = getParentNode(pBinSearchTree->pRootNode, key, &pParentNode);
    if (0 == ret) {
        return ret;
    }

    pNewNode = createNewBinSearchTreeNode(key, value);
    if (NULL == pNewNode) {
        return 0;
    }

    insertNewBinSearchTreeNode(pBinSearchTree, pParentNode, pNewNode);

    return ret;
}

BinSearchTreeNode *searchWithParentNodeBST(BinSearchTree *pBinSearchTree, int key, BinSearchTreeNode **ppParentNode) {
    BinSearchTreeNode *pReturn = NULL;
    BinSearchTreeNode *pParentNode = NULL;

    if (pBinSearchTree == NULL) {
        return NULL;
    }
    pReturn = pBinSearchTree->pRootNode;
    while (pReturn != NULL) {
        if (key == pReturn->key) {
            break;
        }
        pParentNode = pReturn;

        if (key < pReturn->key) {
            pReturn = pReturn->pLeftChild;
        } else {
            pReturn = pReturn->pRightChild;
        }
    }

    if (NULL != ppParentNode) {
        *ppParentNode = pParentNode;
    }

    return pReturn;
}

void deleteNodeNoChild(BinSearchTree *pBinSearchTree, BinSearchTreeNode *pParentNode, BinSearchTreeNode *pDelNode) {
    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == pDelNode) {
            pParentNode->pLeftChild = NULL;
        } else {
            pParentNode->pRightChild = NULL;
        }
    } else {
        pBinSearchTree->pRootNode = NULL;
    }
}

void deleteNodeOneChild(BinSearchTree *pBinSearchTree, BinSearchTreeNode *pParentNode, BinSearchTreeNode *pDelNode) {
    BinSearchTreeNode *pChildNode = NULL;

    if (pDelNode->pLeftChild != NULL) {
        pChildNode = pDelNode->pLeftChild;
    } else {
        pChildNode = pDelNode->pRightChild;
    }

    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == pDelNode) {
            pParentNode->pLeftChild = pChildNode;
        } else {
            pParentNode->pRightChild = pChildNode;
        }
    } else {
        pBinSearchTree->pRootNode = pChildNode;
    }
}

void deleteNodeTwoChildren(BinSearchTree *pBinSearchTree, BinSearchTreeNode *pParentNode, BinSearchTreeNode *pDelNode) {
    BinSearchTreeNode *pPredecessor = NULL, *pSuccessor = NULL;

    pPredecessor = pDelNode;
    pSuccessor = pDelNode->pLeftChild;

    while (pSuccessor->pRightChild != NULL) {
        pPredecessor = pSuccessor;
        pSuccessor = pSuccessor->pRightChild;
    }

    pPredecessor->pRightChild = pSuccessor->pLeftChild;
    pSuccessor->pLeftChild = pDelNode->pLeftChild;
    pSuccessor->pRightChild = pDelNode->pRightChild;

    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == pDelNode) {
            pParentNode->pLeftChild = pSuccessor;
        } else {
            pParentNode->pRightChild = pSuccessor;
        }
    } else {
        pBinSearchTree->pRootNode = pSuccessor;
    }
}

int deleteDataBST(BinSearchTree *pBinSearchTree, int key) {
    int ret = 1;
    BinSearchTreeNode *pDelNode = NULL, *pParentNode = NULL;

    if (pBinSearchTree == NULL) {
        ret = 0;
        return ret;
    }
    pDelNode = searchWithParentNodeBST(pBinSearchTree, key, &pParentNode);
    if (pDelNode == NULL) {
        printf("오류,존재하지 않는 키-[%d],deleteDataBST()\n", key);
        ret = 0;
        return ret;
    }

    if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
        deleteNodeNoChild(pBinSearchTree, pParentNode, pDelNode);
    } else if (pDelNode->pLeftChild != NULL && pDelNode->pRightChild != NULL) {
        deleteNodeTwoChildren(pBinSearchTree, pParentNode, pDelNode);
    } else {
        deleteNodeOneChild(pBinSearchTree, pParentNode, pDelNode);
    }

    free(pDelNode);
    return ret;
}

void deleteBinSearchTreeInternal(BinSearchTreeNode *pTreeNode) {
    if (pTreeNode != NULL) {
        deleteBinSearchTreeInternal(pTreeNode->pLeftChild);
        deleteBinSearchTreeInternal(pTreeNode->pRightChild);
        free(pTreeNode);
    }
}

void deleteBinSearchTree(BinSearchTree *pBinSearchTree) {
    if (pBinSearchTree != NULL) {
        deleteBinSearchTreeInternal(pBinSearchTree->pRootNode);
        free(pBinSearchTree);
    }
}

void displayBinSearchTree(BinSearchTreeNode *pTreeNode, int level, char type) {
    int i = 0;

    if (pTreeNode != NULL) {
        for (i = 0; i < level; i++) {
            printf("    ");
        }

        printf("-(%c)-key: %i,value-%c\n", type,
               pTreeNode->key, pTreeNode->value);

        displayBinSearchTree(pTreeNode->pLeftChild, level + 1, 'L');
        displayBinSearchTree(pTreeNode->pRightChild, level + 1, 'R');
    }

}

int main(int argc, char *argv[]) {
    BinSearchTree *pTree = NULL;
    BinSearchTreeNode *pSearchNode = NULL;
    int key = 0;

    pTree = createBinSearchTree();
    if (pTree != NULL) {
        insertDataBST(pTree, 70, 'A');
        insertDataBST(pTree, 40, 'B');
        insertDataBST(pTree, 90, 'C');
        insertDataBST(pTree, 20, 'D');
        insertDataBST(pTree, 60, 'E');
        insertDataBST(pTree, 80, 'F');
        insertDataBST(pTree, 100, 'G');
        insertDataBST(pTree, 10, 'H');
        insertDataBST(pTree, 30, 'I');
        insertDataBST(pTree, 50, 'J');
        displayBinSearchTree(pTree->pRootNode, 0, '-');


        key = 30;
        pSearchNode = searchBST(pTree, key);
        if (pSearchNode != NULL) {
            printf("검색: 키-[%d],자료-[%c]발견하였습니다\n\n", key, pSearchNode->value);
        } else {
            printf("검색: 키-[%d],발견하지 못하였습니다\n\n", key);
        }

        key = 70;
        printf("자료 제거: 키-[%d]\n", key);
        deleteDataBST(pTree, key);
        displayBinSearchTree(pTree->pRootNode, 0, '-');

        key = 35;
        pSearchNode = searchBST(pTree, key);
        if (pSearchNode != NULL) {
            printf("검색: 키-[%d],자료-[%c]발견하였습니다\n\n", key, pSearchNode->value);
        } else {
            printf("검색: 키-[%d],발견하지 못하였습니다\n\n", key);
        }

        deleteBinSearchTree(pTree);
    }

    return 0;
}
