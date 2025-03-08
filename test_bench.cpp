#include "synthesize.hpp"
#include "io_util.h"
int main()
{
    Anstype ref;
    ref.BFS[0] = 1;
    ref.BFS[1] = 2;
    ref.BFS[2] = 2;
    ref.BFS[3] = 1;
    ref.BFS[4] = 2;
    ref.BFS[5] = 3;
    ref.BFS[6] = 1;
    ref.BFS[7] = 1;
    ref.BFS[8] = 2;
    ref.BFS[9] = 2;

    for (int i = 0 ; i < 10 ; i++)
    { ref.PageRank[i] = 0.1; }

    for (int i = 0 ; i < 10 ; i++)
    { ref.CC[i] = 0; }

    ref.BC[0] = 2;
    ref.BC[1] = 0.25;
    ref.BC[2] = 0.5;
    ref.BC[3] = 9;
    ref.BC[4] = 0;
    ref.BC[5] = 0;
    ref.BC[6] = 2;
    ref.BC[7] = 2;
    ref.BC[8] = 0;
    ref.BC[9] = 0.25;

    ref.TC = 1;

    ref.SSSP[0] = 1;
    ref.SSSP[1] = 2;
    ref.SSSP[2] = 2;
    ref.SSSP[3] = 0;
    ref.SSSP[4] = 2;
    ref.SSSP[5] = 3;
    ref.SSSP[6] = 1;
    ref.SSSP[7] = 1;
    ref.SSSP[8] = 2;
    ref.SSSP[9] = 2;

    Anstype out;
    uint32_t num_nodes;
    uint64_t num_edges;
    pair_uint *edges = get_edges_from_file_adj_sym(std::string("/home/sail/lyf/synthesize_terrace/small.adj"), &num_edges,&num_nodes);
    topfun(num_nodes, num_edges, edges, out);
    free (edges);
    
    if (ref.TC != out.TC)
    {
        std::cout << "WA at TC: \n" << "expect :" 
        << ref.TC << " actual :" << out.TC;
        return -1;
    }
    for (int i = 0 ; i < 10 ; i++)
    {
        if (ref.BFS[i] != out.BFS[i])
        {
            std::cout << "WA at BFS: \n" << "expect :" 
            << ref.BFS[i] << " actual :" << out.BFS[i];
            return -1;
        }
        if (ref.PageRank[i] != out.PageRank[i])
        {
            std::cout << "WA at PageRank: \n" << "expect :" 
            << ref.PageRank[i] << " actual :" << out.PageRank[i];
            return -1;
        }
        if (ref.CC[i] != out.CC[i])
        {
            std::cout << "WA at CC: \n" << "expect :" 
            << ref.CC[i] << " actual :" << out.CC[i];
            return -1;
        }
        if (ref.BC[i] != out.BC[i])
        {
            std::cout << "WA at BC: \n" << "expect :" 
            << ref.BC[i] << " actual :" << out.BC[i];
            return -1;
        }
        if (ref.SSSP[i] != out.SSSP[i])
        {
            std::cout << "WA at SSSP: \n" << "expect :" 
            << ref.SSSP[i] << " actual :" << out.SSSP[i];
            return -1;
        }
    }
    std::cout << "all right" << std::endl;
    return 0;
    
}