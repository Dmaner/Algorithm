# 树

## 经典例题

### 树的基本操作

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

### 线段树

[洛谷 p3372 线段树 1](https://www.luogu.com.cn/problem/P3372)

```c++
    #include <iostream>
    typedef long long LL;

    using namespace std;

    LL a[100000+5], tree[270000], lazy[270000];

    void build(int l, int r, int index)
    {
        if (l == r)
        {
            tree[index] = a[l];
            return;
        }
        int m = l + (r - l) /2;
        build(l, m, index << 1);
        build(m + 1, r, (index << 1) + 1);
        tree[index] = tree[index << 1] + tree[(index << 1) + 1];
    }

    void update(int l, int r, LL delta, int s, int t, int index)
    {
        if (l<= s && t <= r)
        {
            tree[index] += (t - s + 1) * delta;
            lazy[index] += delta;
            return;
        }
        int m = s + (t - s) / 2;
        if (lazy[index])
        {
            tree[index << 1] += lazy[index] * (m - s + 1);
            tree[(index << 1) + 1] +=  lazy[index] * (t - m);
            lazy[index << 1] += lazy[index];
            lazy[(index << 1) + 1] += lazy[index]; 
        }
        lazy[index] = 0;
        // 左儿子和查询区间有交集
        if (l <= m)
        {
            update(l, r, delta, s, m, index << 1);
        }
        // 同理右区间
        if (r > m)
        {
            update(l, r, delta, m + 1, t, (index << 1) + 1);
        }
        tree[index] = tree[index << 1] + tree[(index << 1) | 1];
    }

    LL getsum(int l, int r, int s, int t, int index)
    {
        if (l <= s && t <= r) return tree[index];
        int m = s + (t - s) / 2;
        if (lazy[index])
        {
            tree[index << 1] += lazy[index] * (m - s + 1);
            tree[(index << 1) + 1] +=  lazy[index] * (t - m);
            lazy[index << 1] += lazy[index];
            lazy[(index << 1) + 1] += lazy[index];
        }
        lazy[index] = 0;
        LL sum = 0;
        if (l <= m)
        {
            sum = getsum(l, r, s, m, index << 1);
        }
        if (r > m)
        {
            sum += getsum(l, r, m + 1, t, (index << 1) + 1);
        }
        return sum;
    }

    int main()
    {
        ios::sync_with_stdio(false);
        LL n, m, k;
        int op, x, y;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        build(1, n, 1);
        while (m --)
        {
            cin >> op;
            if (op == 1)
            {
                cin >> x >> y >> k;
                update(x, y, k, 1, n, 1);
            }
            else 
            {
                cin >> x >> y;
                cout << getsum(x, y, 1, n, 1) << endl;
            }
        }
        return 0;
    }
```



## 其他例题

