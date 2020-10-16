#include<iostream>
#include<bits/stdc++.h>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
 };

TreeNode * build_tree(TreeNode* &head, int a[], int length, int index){
    if(index < length){
        head = new TreeNode;
        head->val = a[index];
        head->left = nullptr;
        head->right = nullptr;
        build_tree(head->left, a, length, index*2+1);
        build_tree(head->right, a, length, index*2+2);

        return head;
    }
    else{
        return nullptr;
    }
}

void preOrder(TreeNode *p){
    // 前序遍历
    if (p){
        cout << p->val << " ";
        preOrder(p->left);
        preOrder(p->right);
    }
}

void inOrder(TreeNode* p){
    // 中序遍历
    if (p){
        inOrder(p->left);
        cout << p->val << " ";
        inOrder(p->right);
    }
}

void postOrder(TreeNode* p){
    // 后序遍历
    if (p){
        inOrder(p->left);
        inOrder(p->right);
        cout << p->val << " ";
    }
}

void preOrder2(TreeNode* p){
    // 前序遍历非递归
    stack<TreeNode* > a;
    while (p != nullptr || !a.empty()){
        while (p){
            cout << p->val << " ";
            a.push(p);
            p = p->left;
        }
        if (!p){
            TreeNode* temp = a.top();
            a.pop();
            if (temp->right){
                p = temp->right;
            }
        }
    }
}

void inOrder2(TreeNode* p){
    // 中序遍历非递归
    stack<TreeNode*> a;
    while (p != nullptr || !a.empty()){
        while (p){
            a.push(p);
            p = p->left;
        }
        if (!p){
            TreeNode* temp = a.top();
            cout << temp->val << " ";
            a.pop();
            if (temp->right){
                p = temp->right;
            }
        }
    }
}

int main()
{
    int a[7] = {1, 2, 3, 4,5,6,7};
    // 1
    // 2, 3
    // 4, 5, 6, 7
    TreeNode* p = nullptr;
    p = build_tree(p, a, 7, 0);
    inOrder2(p);
    return 0;
}
