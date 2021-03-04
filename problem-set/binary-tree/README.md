# 二叉树

节点定义

```c++
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

## 经典算法

- LeetCode 144 前序遍历 

```c++
/* 递归 */
class Solution {
public:
    void func(TreeNode* root, vector<int> &ans )
    {
        if (!root) return;
        ans.push_back(root->val);
        func(root->left, ans);
        func(root->right, ans);
    }
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int> ans;
        func(root, ans);
        return ans;
    }
};

/* 迭代 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;

        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while (!stk.empty() || cur)
        {
            while (cur)
            {
                stk.push(cur);
                ans.push_back(cur->val);
                cur = cur->left;   
            }
            cur = stk.top();
            stk.pop();
            cur = cur->right;
        } 
        return ans;
    }
};
```

- LeetCode 94 中序遍历

```c++
/* 迭代 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;

        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while (!stk.empty() || cur)
        {
            while (cur)
            {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            ans.push_back(cur->val);
            cur = cur->right;
        }
        return ans;
    }
};
```

- LeetCode 145 后序遍历

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                st.push(node);                          // 中
                st.push(NULL);

                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左

            } else {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};
```


## 其他例题

- 