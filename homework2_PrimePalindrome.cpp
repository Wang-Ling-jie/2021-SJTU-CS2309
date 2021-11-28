#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Solution
{
public:
    int primePalindrome(int n)
    {
        for (int num = n;; ++num)
        {
            if (isPrime(num) && isPalindrome(num))
                return num;
        }
    }
    bool isPrime(int num)
    {
        if (num % 2 == 0)
            return false;
        int n = 3;
        for (; n <= sqrt(num); n += 2)
        {
            if (num % n == 0)
                return false;
        }
        return true;
    }

    bool isPalindrome(int num)
    {
        vector<int> vec;
        while (num > 0)
        {
            vec.push_back(num % 10);
            num /= 10;
        }
        vector<int>::iterator itr1 = vec.begin();
        vector<int>::iterator itr2 = vec.end() - 1;
        while (itr1 <= itr2)
        {
            if (*itr1 != *itr2)
                return false;
            ++itr1;
            --itr2;
        }
        return true;
    }
};

int main()
{
    Solution s;
    int n;
    cin >> n;
    cout << s.primePalindrome(n) << endl;
    return 0;
}