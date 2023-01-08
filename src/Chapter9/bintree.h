#ifndef _BINTREE_
#define _BINTREE_

typedef struct BinTreeNodeType {
    char data;

    struct BinTreeNodeType *pLeftChild;
    struct BinTreeNodeType *pRightChild;
} BinTreeNode;

typedef struct BinTreeType {
    struct BinTreeNodeType *pRootNode;
} BinTree;

BinTreeNode *makeNewNodeBT(char data);

BinTree *makeBinTree(char rootNodeData);

BinTreeNode *addLeftChildNodeBT(BinTreeNode *pParentNode, char data);

BinTreeNode *addRightChildNodeBT(BinTreeNode *pParentNode, char data);

BinTreeNode *getRootNodeBT(BinTree *pBinTree);

void deleteBinTreeNode(BinTreeNode *pNode);

void deleteBinTree(BinTree *pBinTree);

#endif
