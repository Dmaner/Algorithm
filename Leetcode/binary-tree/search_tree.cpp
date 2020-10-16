#include "tree_nodes.h"

Node* search(Node* head, int val){
    if (head==nullptr){
        return head;
    }
    if (head->val == val){
        return head;
    }
    else if (head->val > val){
        return search(head->left, val);
    }
    else{
        return search(head->right, val);
    }
}

// binary search tree delete

Node* tree_delete(Node* head, Node* z){
    if (z->left&&z->right){
        Node* y = tree_minimum(z->right);
        if (y->parent!=z){
            head = transplant(head, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        head = transplant(head, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    else if (z->left){
        head = transplant(head, z, z->left);
    }
    else{
        head = transplant(head, z, z->right);
    }
    return head;
}

int main()
{
    Node* tree = sample_tree();
    Node* node = search(tree, 1);
    tree = tree_delete(tree, node);
    if (!node) std::cout << "can't find node" << std::endl;
    std::cout << "delete node: " << node->val << std::endl;
    tree_print(tree);
    return 0;
}
