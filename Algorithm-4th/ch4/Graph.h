#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

class Graph;

class Graph
{
private:
    int V;
    int E;
    std::vector<std::vector<int>> adjs;

public:
    Graph(int num);
    Graph(std::istream &os);
    int points();
    int edges();
    // 添加一条边
    void addedge(int v, int w);
    // 返回相邻节点
    std::vector<int> adj(int v);

    std::string toString();
};

std::string Graph::toString()
{
    std::string s = std::to_string(V) + " vertices, " + std::to_string(E) + " edges\n";
    for (int v = 0; v < V; v++)
    {
        s += v + ": ";
        for (int w : this->adj(v))
            s += w + " ";
        s += "\n";
    }
    return s;
}

Graph::Graph(int v)
{
    V = v;
    E = 0;
    this->adjs = std::vector<std::vector<int>>();
    for (int i = 0; i < V; i++)
        adjs[i] = std::vector<int>();
}

Graph::Graph(std::istream &os)
{
    os >> V;
    int es;
    os >> es;
    this->adjs = std::vector<std::vector<int>>();
    for (int i = 0; i < es; i++)
    {
        int v, w;
        os >> v >> w;
        addedge(v, w);
    }
}

int Graph::points() { return V; }
int Graph::edges() { return E; }

void Graph::addedge(int v, int w)
{
    adjs[v].push_back(w);
    adjs[w].push_back(v);
    E++;
}

std::vector<int> Graph::adj(int v)
{
    return adjs[v];
}

// 计算点的度数
static int degree(Graph g, int v)
{
    int degree = 0;
    for (int w : g.adj(v))
        degree++;
    return degree;
}

static int maxDegree(Graph g)
{
    int res = 0;
    for (int v = 0; v < g.points(); v++)
        res = std::max(res, degree(g, v));
    return res;
}

// 计算平均度数
static double avgDegree(Graph g)
{
    return 2.0 * g.edges() / g.points();
}

static int numberOfSelfLoop(Graph g)
{
    int counts = 0;
    for (int v = 0; v < g.points(); v++)
    {
        for (int v : g.adj(v))
        {
            counts++;
        }
    }
    return counts / 2;
}

#endif