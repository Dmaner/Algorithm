#include "Graph.hpp"

void DFS(Graph& graph)
{
    for (auto i = 0; i < graph.nodes.size(); i++)
    {
        node* u = graph.nodes[i];
        u->pre = nullptr;
        u->color = WHITE;
    }
    for (auto & n: graph.nodes)
    {
        if (n->color == WHITE) 
        {
            DFS_VISIT(graph, n);
        }
    }
}

void DFS_VISIT(Graph& graph, node* u)
{
    u->color = GRAY;
    node* v = u;
    while(v->next)
    {
        v = v->next;
        if (v->color == WHITE)
        {
            v->pre = u;
            DFS_VISIT(graph, v);
        }
    }
    u->color = BLACK;
}