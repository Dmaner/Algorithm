#ifndef TREE_NODES_H
#define TREE_NODES_H
#include<iostream>
#include<queue>

class Node{
public:
    Node(int v): val(v), left(nullptr), right(nullptr), parent(nullptr){};
    Node(int v, Node* l, Node* r, Node* p): val(v), left(l), right(r), parent(p){};
    int val;
    Node * left;
    Node * right;
    Node * parent;
};

Node* sample_tree(){
    // 4
    // 2 6
    // 1 3 5 
    Node*head = new Node(4);
    head->left = new Node(2);
    head->left->parent = head;
    head->right = new Node(6);
    head->right->parent = head;
    head->left->left = new Node(1);
    head->left->left->parent = head->left;
    head->left->right = new Node(3);
    head->left->right->parent = head->left;
    head->right->left = new Node(5);
    head->right->left->parent = head->right;

    return head;
}

void queue_clear(std::queue<Node*> &q){
    std::queue<Node*> empty;
    std::swap(empty, q);
}

void tree_print(Node* head){
    std::queue<Node*> q1, q2;
    q1.push(head);
    while (!q1.empty())
    {
        while (!q1.empty()){
            Node* p = q1.front();
            q1.pop();
            if (p){
                std::cout << p->val << " ";
                q2.push(p->left);
                q2.push(p->right);
            }
            else{
                std::cout << "Nil ";
            }
        }
        std::cout << std::endl;
        q1 = q2;
        queue_clear(q2);
    }
    
}

Node* tree_minimum(Node* head){
    if (head){
        Node* x; 
        while (head){
            x = head;
            head = head->left;
        }
        return x;
    }
    else{
        return nullptr;
    }
}

Node* transplant(Node* root, Node* p, Node* q){
    // replace tree p (root p) by tree and p
    if (p == root){
        return q;
    }
    else{
        if (p->parent->left == p) p->parent->left = q;
        else p->parent->right = q;
        if (q) q->parent = p->parent;
        return root;
    }
}

#endif 