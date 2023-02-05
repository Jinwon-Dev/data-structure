#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_GRAPH_TYPE_DIRECT 0
#define ARRAY_GRAPH_TYPE_UNDIRECT 1

typedef struct ArrayGraphType {
    int graphType; // 그래프의 종류 : 방향 그래프, 무방향 그래프
    int nodeCount; // 최대 노드 개수
    int **ppEdge; // 간선 저장을 위한 2차원 배열
} ArrayGraph;

ArrayGraph *createArrayGraph(int graphType, int nodeCount) {
    int i = 0;
    ArrayGraph *pReturn = NULL;

    pReturn = (ArrayGraph *) malloc(sizeof(ArrayGraph));
    if (pReturn == NULL) {
        return NULL;
    }

    pReturn->graphType = graphType;
    pReturn->nodeCount = nodeCount;
    pReturn->ppEdge = (int **) malloc(sizeof(int *) * nodeCount);
    if (pReturn->ppEdge == NULL) {
        return NULL;
    }

    for (i = 0; i < nodeCount; i++) {
        pReturn->ppEdge[i] = (int *) malloc(sizeof(int) * nodeCount);
        if (pReturn->ppEdge[i] == NULL) {
            return NULL; // 중간에 할당된 메모리 해제 필요
        }
        memset(pReturn->ppEdge[i], 0, sizeof(int) * nodeCount);
    }

    return pReturn;
}

int checkVertexValid(ArrayGraph *pGraph, int node) {
    if (pGraph != NULL && node < pGraph->nodeCount && node >= 0) {
        return 1;
    } else {
        return 0;
    }
}

int addEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        pGraph->ppEdge[fromNode][toNode] = 1;
    } else {
        ret = -1;
    }

    return ret;
}

int addEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    ret = addEdgeInternalAG(pGraph, fromNode, toNode);
    if (0 == ret && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = addEdgeInternalAG(pGraph, toNode, fromNode);
    }

    return ret;
}


int removeEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;


    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        pGraph->ppEdge[fromNode][toNode] = 0;
    } else {
        ret = -1;
    }

    return ret;
}

int removeEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    ret = removeEdgeInternalAG(pGraph, fromNode, toNode);
    if (0 == ret && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = removeEdgeInternalAG(pGraph, toNode, fromNode);
    }

    return ret;
}

int getEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        ret = pGraph->ppEdge[fromNode][toNode];
    }

    return ret;
}

void displayGraphAG(ArrayGraph *pGraph) {
    int i = 0, j = 0;
    int count = 0;

    if (pGraph != NULL) {
        count = pGraph->nodeCount;
        for (i = 0; i < count; i++) {
            for (j = 0; j < count; j++) {
                printf("%d ", getEdgeAG(pGraph, i, j));
            }
            printf("\n");
        }
    }
}

void deleteGraphAG(ArrayGraph *pGraph) {
    int i = 0;

    if (pGraph != NULL) {
        for (i = 0; i < pGraph->nodeCount; i++) {
            free(pGraph->ppEdge[i]);
        }
        free(pGraph->ppEdge);
        free(pGraph);
    }
}

int main(int argc, char *argv[]) {
    int nodeCount = 6;
    ArrayGraph *pG1 = createArrayGraph(ARRAY_GRAPH_TYPE_UNDIRECT, nodeCount);
    if (pG1 != NULL) {
        addEdgeAG(pG1, 0, 1);
        addEdgeAG(pG1, 0, 2);
        addEdgeAG(pG1, 1, 2);
        addEdgeAG(pG1, 2, 3);
        addEdgeAG(pG1, 3, 4);
        addEdgeAG(pG1, 3, 5);
        addEdgeAG(pG1, 4, 5);

        printf("G1: 무방향 그래프\n");
        displayGraphAG(pG1);

        deleteGraphAG(pG1);
    }

    return 0;
}
