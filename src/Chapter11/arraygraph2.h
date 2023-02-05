#ifndef _ARRAY_GRAPH
#define _ARRAY_GRAPH

#define ARRAY_GRAPH_TYPE_DIRECT 0
#define ARRAY_GRAPH_TYPE_UNDIRECT 1

typedef struct ArrayGraphType {
    int graphType;
    int nodeCount; // 최대 노드 개수
    int **ppEdge; // 간선 저장을 위한 2차원 배열
} ArrayGraph;

ArrayGraph *createArrayGraph(int graphType, int nodeCount);

int addEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode);

int removeEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode);

int getEdgeAG(ArrayGraph *pGraph, int fromNode, int toNode);

void displayGraphAG(ArrayGraph *pGraph);

void deleteGraphAG(ArrayGraph *pGraph);

#endif
