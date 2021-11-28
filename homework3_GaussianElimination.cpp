#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// Implement your Gaussian Elimination algorithm.
// You can add any standard library if needed.
//
vector<double> Gaussian(vector<double> a[], int num)
{
    vector<double> result;
    double tmp;
    for (int i = 0; i < num - 1; ++i)
    {
        for (int j = i + 1; j < num; ++j)
        {
            if (a[i][i] == 0)
            {
                cout << "No unique solution!";
                exit(-1);
            }
            tmp = a[j][i] / a[i][i];
            for (int k = i; k < num; ++k)
            {
                a[j][k] = a[j][k] - tmp * a[i][k];
            }
            a[j][num] -= tmp * a[i][num];
        }
    }
    if (a[num - 1][num - 1] == 0 && a[num - 1][num != 0])
    {
        cout << "No solution!";
        exit(-1);
    }
    a[num - 1][num] /= a[num - 1][num - 1];
    a[num - 1][num - 1] = 1;

    for (int j = num - 1; j >= 0; --j)
    {
        for (int k = j + 1; k < num; ++k)
        {
            a[j][num] -= a[j][k] * a[k][num];
        }
        if (a[j][j] == 0)
        {
            cout << "No solution!";
            exit(-1);
        }
        a[j][num] /= a[j][j];
        a[j][j] = 1;
        result.push_back(a[j][num]);
    }
    return result;
}

// Test your implementation.
int main()
{
    // Input processing.
    vector<double> result;
    int i = 0;
    vector<double>::iterator itr;
    string str[20];
    double a;
    while (getline(cin, str[i]))
    {
        i++;
    }
    vector<double> vec[20];

    stringstream sstr;
    for (int j = 0; j < i; ++j)
    {
        sstr << str[j];
        while (sstr >> a)
        {
            vec[j].push_back(a);
        }
        sstr.clear();
    }
    result = Gaussian(vec, i);
    // Solve the linear system and print the results.
    for (itr = result.end() - 1; itr >= result.begin(); --itr)
    {
        cout << setiosflags(ios::fixed) << setprecision(3) << *itr << ' ';
    }
    return 0;
}