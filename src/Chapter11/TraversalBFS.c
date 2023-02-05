#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedqueue.h"
#include "arraygraph2.h"

void traversalBFS(ArrayGraph *pGraph, int startNodeID) {
    int i = 0;
    int nodeID = 0;
    LinkedQueue *pQueue = NULL;
    LinkedQueueNode *pQueueNode = NULL;
    int *pVisit = NULL;

    if (pGraph == NULL) { // 그래프가 NULL인지 점검
        return;
    }

    pQueue = createLinkedQueue(); // 큐의 생성 및 노드 방문 여부를 저장하는 동적 배열 할당
    pVisit = malloc(sizeof(int) * pGraph->nodeCount);

    if (pQueue == NULL || pVisit == NULL) { // 유효성 점검 및 큐, 배열에 대한 NULL 여부 점검
        return;
    }

    memset(pVisit, 0, sizeof(int) * pGraph->nodeCount); // 노드 방문 여부를 모두 0으로 초기화
    pVisit[startNodeID] = 1;
    enqueueLQ(pQueue, startNodeID);

    while (isLinkedQueueEmpty(pQueue) == 0) {
        pQueueNode = dequeueLQ(pQueue);
        if (pQueueNode != NULL) {
            nodeID = pQueueNode->data;
            printf("노드-[%d] 방문\n", nodeID);

            for (i = 0; i < pGraph->nodeCount; i++) {
                if (i != nodeID) { // 종료 노드가 디큐한 노드가 되어서는 안 됨
                    if (0 != getEdgeAG(pGraph, nodeID, i)) { // 간선이 존재하는 노드인지 점검
                        if (0 == pVisit[i]) { // 기존에 방문한 적이 없는 노드여야 함
                            pVisit[i] = 1; // 방문 처리하고 큐에 인큐
                            enqueueLQ(pQueue, i);
                        }
                    }
                }
            }
            free(pQueueNode);
        }
    }

    deleteLinkedQueue(pQueue);
    free(pVisit);
}

int main(int argc, char *argv[]) {
    int nodeCount = 4;
    ArrayGraph *pG1 = createArrayGraph(ARRAY_GRAPH_TYPE_UNDIRECT, nodeCount);

    if (pG1 != NULL) {
        addEdgeAG(pG1, 0, 1);
        addEdgeAG(pG1, 0, 2);
        addEdgeAG(pG1, 1, 3);

        printf("G1: BFS\n");
        traversalBFS(pG1, 0);

        deleteGraphAG(pG1);
    }

    return 0;
}
