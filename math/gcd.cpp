#include <iostream>

int gcd(int a, int b) { return b == 0 ? a : gcd(b, b % a); }

int lcm(int a, int b) { return a * b / gcd(a, b); }

/*
扩展欧几里得算法
*/
int xGCD(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1, gcd = xGCD(b, b % a, x1, y1);
  x = y1, y = x1 - (a / b) * y1;
  return gcd;
}