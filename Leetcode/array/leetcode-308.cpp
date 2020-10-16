#include <bits/stdc++.h>

using namespace std;

class NumMatrix
{
public:
    int n, m;
    vector<vector<int>> bits;
    vector<vector<int>> mat;
    NumMatrix(vector<vector<int>> &matrix): mat(matrix)
    {
        m = matrix.size();
        if (m)
            n = matrix[0].size();
        else
            n = 0;
        bits = vector<vector<int>>(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                modify(i + 1, j + 1, matrix[i][j]);
    }

    inline int lowbit(int x) { return x & (-x); }

    void modify(int x, int y, int delta)
    {
        for (int i = x; i <= m; i += lowbit(i))
        {
            for (int j = y; j <= n; j += lowbit(j))
            {
                bits[i][j] += delta;
            }
        }
    }

    void update(int row, int col, int val)
    {
        int delta = val - mat[row][col];
        modify(row + 1, col + 1, delta);
        mat[row][col] = val;
    }

    int presum(int x, int y)
    {
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                res += bits[i][j];
        return res;
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return presum(row2 + 1, col2 + 1) - presum(row1, col2 + 1) - presum(row2 + 1, col1) + presum(row1, col1);
    }
};
