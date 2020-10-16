#include <iostream>
#include <random>

// using rand m function to build rand n
// m < n and m*m >= n
int randm();

int randm_n(int m, int n)
{
    int x = 0;
    do
    {
        x = m * (randm() - 1) + randm();
    } while (x >= n);
    return x;
}