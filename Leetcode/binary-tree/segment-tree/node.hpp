#ifndef NODE_H
#define NODE_H

#include <iostream>

class SegmentTree
{
    public:
        friend std::ostream& operator<< (std::ostream&, SegmentTree*);
        int left_value;  // 左端点值
        int right_value; //右端点值
        int cover;       // 覆盖次数

        // 左右节点
        SegmentTree* left;
        SegmentTree* right;
        
        SegmentTree(): left_value(0), right_value(0), cover(0), left(nullptr), right(nullptr) {}
        
};

std::ostream& operator<< (std::ostream& os, SegmentTree* root)
{
    std::cout << "Left value: " + root->left_value << std::endl;
    std::cout << "Right value: " + root->right_value << std::endl;
    std::cout << "Cover: " + root->cover << std::endl;
}

#endif