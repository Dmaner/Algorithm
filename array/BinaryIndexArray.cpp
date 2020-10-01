#include <vector>
#include <iostream>

using namespace std;

class BinaryIndexArray
{
private:
    vector<int> bits;
    int lowbit(int x)
    {
        return (x & (-x));
    }

public:
    BinaryIndexArray(vector<int> &arr)
    {
        bits.resize(arr.size() + 1);
        for (int i = 0; i < arr.size(); i++)
            bits[i + 1] = arr[i];

        for (int i = 1; i < bits.size(); i++)
        {
            int j = i + lowbit(i);
            if (j < bits.size())
            {
                bits[j] += bits[i];
            }
        }
    }

    void update(int, int);
    int prefixsum(int);
    int rangesum(int, int);
};

void BinaryIndexArray::update(int index, int delta)
{
    ++index;
    while (index < bits.size())
    {
        bits[index] += delta;
        index += lowbit(index);
    }
}

int BinaryIndexArray::prefixsum(int index)
{
    ++index;
    int result = 0;
    while (index > 0)
    {
        result += bits[index];
        index -= lowbit(index);
    }
    return result;
}

int BinaryIndexArray::rangesum(int from_index, int to_index)
{
    return prefixsum(to_index) - prefixsum(from_index - 1);
}

int main(int argc, char const *argv[])
{
    vector<int> test{0, 1, 2, 3, 4, 5, 6, 7};
    BinaryIndexArray a(test);
    cout << a.prefixsum(2) << endl;
    a.update(0, 2);
    cout << a.prefixsum(2) << endl;
    cout << a.rangesum(0, 5) << endl;
    return 0;
}
