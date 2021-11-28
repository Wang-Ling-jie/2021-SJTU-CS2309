#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;


// You can add additional standard libraries if necessary.
// Implement the Newton interpolation!
class Newton {
public:
    Newton(vector<double> x, vector<double> y): X(x), Y(y) {}

    double result(double interp_x){
        vector<double>Z;
        vector<double>W;
        for(int i=0;i<X.size();i++){
            Z.push_back(X[i]);
            W.push_back(Y[i]);
        }
        double result=0;
        double ss;
        double *a=new double[X.size()];
        int pos=0;

        double h=X[1]-X[0];

        //compute a[i]
        for(int i=0;i<Y.size();++i){
            a[pos]=Y[0];

            for(int j=1;j<=i;++j){
                a[pos]/=(j*h);
            }
            //replate Y[i] as delta Y[i] 
            for(int j=0;j<Y.size()-i-1;++j) Y[j]=Y[j+1]-Y[j];
            pos++;
        }

        for(int i=0;i<X.size();++i){
            ss=a[i];
            for(int j=0;j<i;++j){
                ss*=interp_x-X[j];
            }
            result+=ss;
        }
        for(int i=0;i<X.size();i++){
            X[i]=Z[i];
            Y[i]=W[i];
        }
        delete []a;
        return result;
    }

private:
    vector<double> X, Y;
};


// Test your implementation.
int main(int argc, const char * argv[]) {
    ofstream os;
    os.open("Newton_interpolation_data_h1");

    //  Input preprocessing.
    string str;
    getline(cin, str);
    stringstream xstr(str);
    getline(cin, str);
    stringstream ystr(str);
    
    // X and Y are two vectors of equal length to be traversed.
    vector<double> X, Y;
    double a;
    while (xstr >> a)
        X.push_back(a);
    while (ystr >> a)
        Y.push_back(a);
    
    // interp_x is the point to be interpolated.
    double interp_x;

    // Do Newton interpolation for interp_x using X and Y, and print your results
    // Note: The result retains three decimal places (rounded)!
    Newton n(X,Y); 
    for(interp_x = -5;interp_x<=5;interp_x+=0.1)
        os<<n.result(interp_x)<<endl;
    
    // End
    return 0;
}
