#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraygraph2.h"

void traversalDFS(ArrayGraph *pGraph, int startNodeID, int *pVisit) {
    int i = 0;

    pVisit[startNodeID] = 1; // 현재 노드 방문 처리
    printf("노드-[%d] 방문\n", startNodeID);

    for (i = 0; i < pGraph->nodeCount; i++) {
        if (i != startNodeID) {
            if (0 != getEdgeAG(pGraph, startNodeID, i)) {
                if (0 == pVisit[i]) {
                    traversalDFS(pGraph, i, pVisit);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int nodeCount = 4; // 8;
    ArrayGraph *pG1 = createArrayGraph(ARRAY_GRAPH_TYPE_UNDIRECT, nodeCount);
    int *pVisit = malloc(sizeof(int) * nodeCount);

    if (pG1 != NULL && pVisit != NULL) {
        addEdgeAG(pG1, 0, 1);
        addEdgeAG(pG1, 0, 2);
        addEdgeAG(pG1, 1, 3);

        // 초기화
        memset(pVisit, 0, sizeof(int) * nodeCount);
        printf("G1: DFS\n");
        traversalDFS(pG1, 0, pVisit);

        deleteGraphAG(pG1);
        free(pVisit);
    }

    return 0;
}
