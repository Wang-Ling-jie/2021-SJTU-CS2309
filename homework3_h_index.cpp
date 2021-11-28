#include <iostream>
#include <vector>
using namespace std;
//0 1 3 5 6
class Solution {
public:
    int hIndex(vector<int>& citations) {
    	// Compute h-index
        quickSort(citations);
        for(int h=citations.size(); h>0;--h){
            if(citations[citations.size()-h]>=h) return h;
        }
    }
    void quickSort(vector<int>& citations){
        quickSort(citations,0,citations.size()-1);
    }
    void quickSort(vector<int>& citations,int low,int high){
        if(low>=high) return;
        int mid=divide(citations,low,high);
        quickSort(citations,low,mid-1);
        quickSort(citations,mid+1,high);
    }

    int divide(vector<int> &citations,int left,int right){
        int pivot=citations[left];
        while(left<right){
            while(citations[right]>pivot&&right>left) --right;
            if(right>left){citations[left]=citations[right];++left;}
            while(left<right&&citations[left]<pivot) ++left;
            if(left<right){citations[right]=citations[left];--right;}
        }
        citations[left]=pivot;
        return left;
    }

};

int main() {
    // Process input line
    Solution sol;
    int x;
    vector<int>vec;
    while(cin>>x){
        vec.push_back(x);
    }
    // Return the result
    cout<<sol.hIndex(vec);
    return 0;
}