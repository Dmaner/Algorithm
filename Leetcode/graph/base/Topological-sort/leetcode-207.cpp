// leetcode 207 link: https://leetcode-cn.com/problems/course-schedule/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    // 采用bfd
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> courses(numCourses, vector<int>());
        vector<int> ans;
        vector<int> indegree(numCourses, 0);
        queue<int> q;
        for (const auto &info : prerequisites)
        {
            courses[info[1]].push_back(info[0]);
            indegree[info[0]]++;
        }

        // 入度为0的节点入队
        for (int i = 0; i < numCourses; i++)
            if (!indegree[i])
                q.push(i);
        
        while (!q.empty())
        {
            int course = q.front();
            q.pop();
            ans.push_back(course);
            for (int id: courses[course])
            {
                if (!--indegree[id]) q.push(id);
            }
        }
        return ans.size() == numCourses;
    }
};