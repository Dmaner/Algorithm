#include "Graph.hpp"
#include <iostream>
#include <queue>

void BFS(Graph& graph, node* s)
{
    // initial
    for (size_t i = 0; i < graph.nodes.size(); i++)
    {
        node* u = graph.nodes[i];
        if (u == s) continue;
        u->color = WHITE;
        u->distance = INT_MAX;
        u->pre = nullptr;
    }
    s->distance = 0;
    s->color = GRAY;
    s->pre = nullptr;
    std::queue<node*> q;
    q.push(s);
    
    // traverse
    while (!q.empty())
    {
        node* u = q.front();
        q.pop();
        node* v = u;
        while (v->next)
        {
            node* v = v->next;
            if (v->color == WHITE)
            {
                v->color = GRAY;
                v->distance = u->distance + 1;
                v->pre = u;
                q.push(v);
            }
        }
        u->color = BLACK;
    }
}