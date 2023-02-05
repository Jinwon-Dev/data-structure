#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DirectArrayGraphType {
    int nodeCount; // 최대 노드 개수
    int **ppEdge; // 간선 저장을 위한 2차원 배열
} DirectArrayGraph;

DirectArrayGraph *createDirectArrayGraph(int nodeCount) {
    int i = 0;
    DirectArrayGraph *pReturn = NULL;

    pReturn = (DirectArrayGraph *) malloc(sizeof(DirectArrayGraph));
    if (pReturn == NULL) { // 방향 그래프 구조체 자체의 메모리 할당 및 검증
        return NULL;
    }

    pReturn->nodeCount = nodeCount; // 노드 개수에 대한 멤버 변수 초기화
    pReturn->ppEdge = (int **) malloc(sizeof(int *) * nodeCount);
    if (pReturn->ppEdge == NULL) { // 포인터 변수들의 1차원 배열을 위한 메모리를 할당하고 검증
        return NULL;
    }

    for (i = 0; i < nodeCount; i++) { // 각각의 줄별로 메모리를 할당하고 검증
        pReturn->ppEdge[i] = (int *) malloc(sizeof(int) * nodeCount);
        if (pReturn->ppEdge[i] == NULL) {
            return NULL; // 중간에 할당된 메모리 해제 필요
        }
        memset(pReturn->ppEdge[i], 0, sizeof(int) * nodeCount); // 각 줄별로 메모리를 0으로 초기화
    }

    return pReturn;
}

int checkVertexValid(DirectArrayGraph *pGraph, int node) {
    if (pGraph != NULL && node < pGraph->nodeCount && node >= 0) {
        return 1;
    } else {
        return 0;
    }
}

int addEdgeDAG(DirectArrayGraph *pGraph, int fromNode, int toNode) {
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

int removeEdgeDAG(DirectArrayGraph *pGraph, int fromNode, int toNode) {
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

int getEdgeDAG(DirectArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        ret = pGraph->ppEdge[fromNode][toNode];
    }

    return ret;
}

void displayGraphDAG(DirectArrayGraph *pGraph) {
    int i = 0, j = 0;
    int count = 0;

    if (pGraph != NULL) {
        count = pGraph->nodeCount;
        for (i = 0; i < count; i++) {
            for (j = 0; j < count; j++) {
                printf("%d ", getEdgeDAG(pGraph, i, j));
            }
            printf("\n");
        }
    }
}

void deleteGraphDAG(DirectArrayGraph *pGraph) {
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
    DirectArrayGraph *pG2 = createDirectArrayGraph(nodeCount);
    if (pG2 != NULL) {
        addEdgeDAG(pG2, 0, 1);
        addEdgeDAG(pG2, 1, 2);
        addEdgeDAG(pG2, 2, 0);
        addEdgeDAG(pG2, 2, 3);
        addEdgeDAG(pG2, 3, 2);
        addEdgeDAG(pG2, 3, 4);
        addEdgeDAG(pG2, 4, 5);
        addEdgeDAG(pG2, 5, 3);

        printf("G2: 방향 그래프\n");
        displayGraphDAG(pG2);

        deleteGraphDAG(pG2);
    }

    return 0;
}
