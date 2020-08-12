// tarjan algorithom 
// leetcode 1192 link: https://leetcode-cn.com/problems/critical-connections-in-a-network/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    int index;
    vector<int> dfn;
    vector<int> low;
    vector<vector<int>> edges;
    vector<vector<int>> ans;
    vector<bool> visited;
public:

    void tarjan(int node, int parent)
    {
        index ++;
        low[node] = index;
        dfn[node] = index;
        visited[node] = true;
        
        for (auto e : edges[node])
        {
            // ignore parent node side effect 
            if (e == parent) continue;
            if (!visited[e])   
            {
                tarjan(e, node);
                low[node] = min(low[node], low[e]);
                
                if (low[e] > dfn[node]) ans.push_back({node, e});
            }
            else  // in the stack
            {
                low[node] = min(low[node], dfn[e]);
            }
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        low = vector<int>(n, 0);
        dfn = vector<int>(n, 0);
        visited = vector<bool>(n, false);
        edges = vector<vector<int>> (n);
        index = 0;
        for (auto conn : connections)
        {
            edges[conn[0]].push_back(conn[1]);
            edges[conn[1]].push_back(conn[0]);
        }
        tarjan(0, -1);
        
        return ans;
    }
};