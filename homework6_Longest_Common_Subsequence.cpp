#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

set<string>s;

void get_LCS(int **b,string X,int i,int j,string str){
    while(i>0&&j>0){
        if(b[i-1][j-1]==1){
            str+=X[i-1];
            --i;
            --j;
        }
        else if(b[i-1][j-1]==2){
            --j;
        }
        else if(b[i-1][j-1]==3){
            --i;
        }
        else if(b[i-1][j-1]==4){
            get_LCS(b,X,i-1,j,str);
            get_LCS(b,X,i,j-1,str);
            return;
        }
    }
    reverse(str.begin(),str.end());
    s.insert(str);
}

set<string> LCS(string X, string Y)
{
    int xlen=X.length();
    int ylen=Y.length();
    int **c=new int*[xlen+1];
    int **b=new int*[xlen];
    for(int i=0;i<xlen;++i){
        b[i]=new int [ylen];
    }
    for(int i=0;i<=xlen;++i){
        c[i]=new int [ylen+1];
    }
    for(int i=0;i<=xlen;++i){
        c[i][0]=0;
    }
    for(int i=0;i<=ylen;++i){
        c[0][i]=0;
    }

    for(int i=1;i<=xlen;++i){        
        for(int j=1;j<=ylen;++j){
            if(X[i-1]==Y[j-1]){
                c[i][j]=c[i-1][j-1]+1;
                b[i-1][j-1]=1;
            }
            else{
                if(c[i][j-1]>c[i-1][j]){
                    c[i][j]=c[i][j-1];
                    b[i-1][j-1]=2;
                }
                else if(c[i][j-1]<c[i-1][j]){
                    c[i][j]=c[i-1][j];
                    b[i-1][j-1]=3;
                }
                else if(c[i][j-1]==c[i-1][j]){
                    c[i][j]=c[i-1][j];
                    b[i-1][j-1]=4;
                }
            }
        }
    }
    for(int i=0;i<xlen;++i){
        for(int j=0;j<ylen;++j){
            cout<<b[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    for(int i=0;i<=xlen;++i){
        for(int j=0;j<=ylen;++j){
            cout<<c[i][j]<<' ';
        }
        cout<<endl;
    }
    get_LCS(b,X,xlen,ylen,"");
    for(int i=0;i<xlen;++i){
        delete []b[i];
        delete []c[i];
    }
    delete []c;
    delete []b;
    return s;
}

int main()
{
	string X, Y;
	cin >> X;
	cin >> Y;

	set<string> lcs = LCS(X, Y);

	// print set elements
	for (string str : lcs)
		cout << str << endl;

	return 0;
}

/*
input:
springtime
printing
output:
    printi

input:
    basketball
    krzyzewski

output:
    ke
    sk
*/