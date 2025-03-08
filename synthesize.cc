
#include "memory_pool.hpp"

#include <iostream>

#include "graph.h"
#include "BFS.h"
#include "Pagerank.h"
#include "Components.h"
#include "BC.h"
#include "TC.h"
#include "BellmanFordUnweighted.h"
#include "synthesize.hpp"
using namespace graphstore;
using std::cout;

void BFS(Graph& G, int ans[])
{
    // struct timeval start, end;
	// struct timezone tzp;
    long src = 3;
    auto bfs_edge_map = BFS_with_edge_map(G, src);
    //   gettimeofday(&end, &tzp);
    for (int i = 0 ; i < 10 ; i++)
    {
        int cur = i;
        int father = bfs_edge_map[i];
        do
        {
            ans[i]++;
            cur = father;
            father = bfs_edge_map[father];
        }
        while (cur != src);
    }
    // cout << "----------------------------------------\n";
    // std::cout << "Running BFS from source = " << src << std::endl;

    // cout << "BFS: result"<<endl;
    // for (int i = 0 ; i < 10 ; i ++)
    // {
    //     cout << i<< "path to "<<src <<" : " << path[i]<<endl; 
    // }
    myfree(bfs_edge_map);
}

void PageRank(Graph& G, double ans[])
{
    long maxiters = 10;
    auto pr_edge_map = PR_S<double>(G, maxiters);
    // cout << "----------------------------------------\n";
    // std::cout << "Running PR" << std::endl;
    // cout << "Pagerank: result"<<endl;
    // for (int i = 0 ; i < 10 ; i ++)
    // {
    //     cout << i <<" : " << pr_edge_map[i]<<endl; 
    // } 
    for (int i = 0 ; i < 10 ; i++)
    {
        ans[i] = pr_edge_map[i];
    }
    myfree(pr_edge_map);
    // PRINT("PR finished");
}

void ConnectedComponents(Graph& G, int ans[])
{
    auto cc_result = CC(G);
    // cout << "----------------------------------------\n";
    // std::cout << "Running CC" << std::endl;
    // cout << "Connected Components : result"<<endl;
    // for (int i = 0 ; i < 10 ; i++)
    // {
    //     cout << "Id " << i << "belongs to : " << cc_result[i] << endl;
    // }
    for (int i = 0 ; i < 10 ; i++)
    {
        ans[i] = cc_result[i];
    }
    myfree(cc_result);
}

void BetweennessCentality(Graph& G, double ans[])
{
    long src = 3;
    // cout << "----------------------------------------\n";
    // std::cout << "Running BC from source = " << src << std::endl;
    auto bc_result = BC(G, src);
    // cout << "Betweenness Centality : result"<<endl;
    // for (int i = 0 ; i < 10 ; i ++)
    // {
    //     cout << i << " : " << bc_result[i]<<endl; 
    // }
    for (int i = 0 ; i < 10 ; i++)
    {
        ans[i] = bc_result[i];
    }
    myfree(bc_result);
}

void TriangleCount(Graph& G, int& ans)
{
    // cout << "----------------------------------------\n";
    // std::cout << "Running TC" << std::endl;
    ans = TC(G);
    // cout << "Triangle Count : result" << endl;
    // cout << count << endl;
}

void SingleSourceShortestPath(Graph& G, int ans[])
{
    // cout << "----------------------------------------\n";
    long src = 3;
    // std::cout << "Running SSSP" << "src: "<< src << std::endl;
    auto result = SSSP_BF(G,src);
    // cout << "Single Source Shortest Path : result" << endl;
    for (int i = 0 ; i < 10 ; i ++)
    {
        ans[i] = result[i]; 
    }
    myfree(result);
}

void topfun(uint32_t num_nodes, uint64_t num_edges, pair_uint *edges, Anstype &ans)
{
    Graph graph (num_nodes);
    // custom_vector<uint32_t> new_srcs(num_edges);
    custom_vector<uint32_t> new_srcs;
    // custom_vector<uint32_t> new_dests(num_edges);
    custom_vector<uint32_t> new_dests;
            for (uint32_t i = 0; i < num_edges; i++) {
            new_srcs[i] = edges[i].x;
            new_dests[i] = edges[i].y;
    }
    auto perm = get_random_permutation(num_edges);
    graph.add_edge_batch(new_srcs.storage, new_dests.storage, num_edges, perm);
    
    BFS(graph, ans.BFS);
    PageRank(graph, ans.PageRank);
    ConnectedComponents(graph, ans.CC);
    BetweennessCentality(graph, ans.BC);
    TriangleCount(graph, ans.TC);
    SingleSourceShortestPath(graph, ans.SSSP);
}