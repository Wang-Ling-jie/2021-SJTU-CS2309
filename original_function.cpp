#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream os;
    os.open("original_function_data");
    for(double i=-5;i<=5;i+=0.1){
        os<<1.0/(1.0+i*i)<<endl;
    }
}