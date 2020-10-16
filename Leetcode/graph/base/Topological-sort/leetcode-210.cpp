// leetcode 210 link: https://leetcode-cn.com/problems/course-schedule-ii/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> visited;
    vector<vector<int>> edges;
    vector<int> ans;
    bool vaild; // 判断是否有环
    void dfs(int course_id)
    {
        visited[course_id] = 1;
        for (auto i : edges[course_id])
        {
            if (!visited[i])
                dfs(i);
            else if (visited[i] == 1){
                vaild = false;
                return; 
            }
        }
        visited[course_id] = 2;
        ans.push_back(course_id);
    }
    // dfs拓扑排序
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        visited.resize(numCourses, 0);
        edges.resize(numCourses, vector<int>());
        ans.clear();
        vaild = true;

        for (const auto &info : prerequisites)
        {
            edges[info[1]].push_back(info[0]);
        }

        for (int i = 0; i < numCourses && vaild; ++i)
        {
            if (!visited[i])
                dfs(i);
        }
        if (!vaild)
            return {};
        reverse(ans.begin(), ans.end());
        return ans;
    }
};