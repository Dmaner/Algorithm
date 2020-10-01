#include "node.hpp"

// 构建线段树
using namespace std;

// 左右端点左闭右开
SegmentTree *CreateTree(int left, int right)
{
    if (right - left < 1)
        return nullptr;
    SegmentTree *root = new SegmentTree();
    root->left_value = left;
    root->right_value = right;
    root->cover = 0;

    // 如果是叶子节点
    if (right - left == 1)
        return root;
    int mid = left + (right - left) / 2;
    root->left = CreateTree(left, mid);
    root->right = CreateTree(mid, right);

    return root;
}

// 插入线段
void InsertNode(int a, int b, SegmentTree *root)
{
    if (a < root->left_value || b > root->right_value || !root)
        return;

    if (root->left_value == a && root->right_value == b)
    {
        root->cover++;
        return;
    }

    int mid = root->left_value + (root->right_value - root->left_value) / 2;
    if (b <= mid)
        InsertNode(a, b, root->left);
    else if (a >= mid)
        InsertNode(a, b, root->right);
    else
    {
        InsertNode(a, mid, root->left);
        InsertNode(mid, b, root->right);
    }
}

// 删除节点
void DeleteNode(int a, int b, SegmentTree *root)
{
    if (a < root->left_value || b > root->right_value || !root)
        return;

    if (root->left_value == a && root->right_value == b)
    {
        root->cover -- ;
        return;
    }

    int mid = root->left_value + (root->right_value - root->left_value) / 2;
    if (b <= mid)
        DeleteNode(a, b, root->left);
    else if (a >= mid)
        DeleteNode(a, b, root->right);
    else
    {
        DeleteNode(a, mid, root->left);
        DeleteNode(mid, b, root->right);
    }
}
