#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

vector<int>::iterator itr;

class Solution
{
public:
    int kthLargestElement(vector<int>::iterator itr, int size, int k)
    {
        int pivot = divide(itr, 0, size - 1);
        if (pivot == size - k)
            return itr[pivot];
        if (pivot < size - k)
            return kthLargestElement(itr + pivot + 1, size - pivot - 1, k);
        if (pivot > size - k)
            return kthLargestElement(itr, pivot, k - (size - pivot));
    }
    int divide(vector<int>::iterator itr, int left, int right)
    {
        int k = itr[left];
        while (left < right)
        {
            while (left < right && itr[right] >= k)
                --right;
            if (left < right)
            {
                itr[left] = itr[right];
                ++left;
            }
            while (left < right && itr[left] <= k)
                ++left;
            if (left < right)
            {
                itr[right] = itr[left];
                --right;
            }
            itr[left] = k;
            return left;
        }
    }
};

int main()
{
    Solution sol;

    string str;
    getline(cin,str);
    stringstream ss(str);

    vector<int>vec;
    int x;
    while(ss>>x){
        vec.push_back(x);
    }
    int k;
    cin >> k;
    cout << sol.kthLargestElement(vec.begin(), vec.size(), k);
    return 0;
}