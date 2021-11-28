 // Add any standard library if needed.
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#define noEdge 257

using namespace std;

// Implement your minimum spinning tree algorithm
int weight(vector<int>vec[],int num){
    bool *flag=new bool[num];
    int *lowCost=new int[num];
    int minCost;
    int totalCost=0;
    for(int i=0;i<num;i++){
        lowCost[i]=noEdge;
        flag[i]=false;
    }

    int start=0;
    for(int i=1;i<num;++i){
        flag[start]=true;
        minCost=noEdge;

        for(int j=0;j<num;j++){
            if(vec[start][j]!=0&&lowCost[j]>vec[start][j]&&flag[j]==false){
                lowCost[j]=vec[start][j];
            }
        }
        for(int k=0;k<num;++k){
            if(lowCost[k]<minCost&&flag[k]==false){
                minCost=lowCost[k];
                start=k;
            }
        }
        lowCost[start]=noEdge;
        totalCost+=minCost;
    }
    delete []flag;
    delete []lowCost;
    return totalCost;
}

// Test your implementation
int main () {
    vector<int> vec[50];
    string str[50];
    int a;
    
    stringstream ss;

    int num=0;
    while(getline(cin,str[num])){
        ++num;
    }
    for(int i=0;i<num;++i){
        ss<<str[i];
        while(ss>>a){
            vec[i].push_back(a);
        }
        ss.clear();
    }
    cout<<weight(vec,num)<<endl;
    return 0;
}