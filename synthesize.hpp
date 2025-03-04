#include "graph.h"
#include <cstring>
using namespace graphstore;
struct Anstype 
{
    int BFS[10];
    double PageRank[10];
    int CC[10];
    double BC[10];
    int TC;
    int SSSP[10];
    Anstype()
    {
        memset(BFS,0,sizeof(BFS));
        memset(PageRank, 0, sizeof(PageRank));
        memset(CC,0,sizeof(CC));
        memset(BC, 0, sizeof(BC));
        memset(SSSP, 0, sizeof(SSSP));
        TC = 0;
    }
};
void BFS(Graph& G, int ans[]);
void PageRank(Graph& G, double ans[]);
void ConnectedComponents(Graph& G, int ans[]);
void BetweennessCentality(Graph& G, double ans[]);
void TriangleCount(Graph& G, int& ans);
void SingleSourceShortestPath(Graph& G, int ans[]);
void BUILD(Anstype& ans);
