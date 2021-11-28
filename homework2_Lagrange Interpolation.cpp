#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;


// You can add additional standard libraries if necessary.
// Implement the Lagrange interpolation!
class Lagrange {
public:
    Lagrange(vector<double> x, vector<double> y): X(x), Y(y) {}

    double result(double interp_x){
        double ss;
        double result=0;
        for(int i=0;i<X.size();++i){
            ss=Y[i];
            for(int j=0;j<X.size();++j){
                if(j!=i)  ss*=(interp_x-X[j])/(X[i]-X[j]);
            }
            result+=ss;
        }
        return result;
    }

private:
    vector<double> X, Y;
};


// Test your implementation.
int main(int argc, const char * argv[]) {
    ofstream os;
    os.open("lagrange_interpolation_data_h1");


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

    Lagrange lg(X,Y);

    // Do Lagrange interpolation for interp_x using X and Y, and print your results
    // Note: The result retains three decimal places (rounded)!
    for(interp_x = -5;interp_x<=5;interp_x+=0.1)
        os<<lg.result(interp_x)<<endl;
    // End
    return 0;
}
