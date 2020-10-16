#include "tree_nodes.h"

class RBTree
{
    // red black tree
public:
    Node *root;
    Node *nil = new Node(-1);
};

// judge if nil node
bool not_nil(Node *node)
{
    return node->val == -1;
}

Node *get_node(RBTree &T, int val)
{
    Node *a = new Node(val, T.nil, T.nil, T.nil);
}

// suppose x's right child node is not nil
// left rotate
void left_rotate(RBTree &T, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    // move y.left to x.right
    if (not_nil(y->left))
        x->left->parent = x;

    y->parent = x->parent;
    if (!not_nil(x->parent))
        T.root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;

    // pu x on y's left
    y->left = x;
    x->parent = y;
}

// right rotate
void right_rotate(RBTree &T, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (not_nil(x->right))
        x->right->parent = y;

    x->parent = y->parent;

    // link y's parent to x
    if (!not_nil(y->parent))
        T.root = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    // put y no x's right
    x->right = y;
    y->parent = x;
}