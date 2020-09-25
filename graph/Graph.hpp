#ifndef GRAPH_H
#define GRAPH_H
#define WHITE 0
#define BLACK 1
#define GRAY 2
#include <iostream>
#include <vector>

class node
{
    public:
        int val;
        int color;
        int distance;
        node* next;
        node* pre;
        node(int x): val(x), color(), distance(INT_MAX), next(nullptr), pre(nullptr) {}
        bool operator==(node& rhs)
        {
            if (this->val != rhs.val) return false;
            if (this->color != rhs.color) return false;
            if (this->distance != rhs.distance) return false;
            return true;
        }
};

class edge
{
    public:
        int weight;
        node* u;
        node* v;
};

class Graph
{
    public:
        std::vector<node*> nodes;
        std::vector<edge*> edgs;
};

void PrintNode(node* root)
{
    if (root == nullptr) std::cout << " NULL " << std::endl;
    else
    {
        std::cout << "Value: "<< root->val << std::endl;
        std::cout << "Color: ";
        if (root->color == WHITE) std::cout << "White"<<std::endl;
        else if (root->color == BLACK) std::cout << "BLACK"<<std::endl;
        else std::cout << "GRAY"<<std::endl;
        std::cout << "Distance: " << root->distance << std::endl;
        std::cout << "Next:";
        while (root->next)
        {
            root = root->next;
            std::cout << " val: " << root->val;
        }
        std::cout <<std::endl;
    }
}

#endif