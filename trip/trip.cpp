#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ifstream fin; 
    ofstream fout;
    fin.open("trip.inp"); 
    fout.open("trip.out");


    int n;

    while(fin >> n){
        if(n == 0){
            break;
        }

        double arr[n];
        double sum = 0.0;
        double Negative = 0.0;
        double Positive = 0.0;

        for (int i = 0; i<n; i++){
            fin >> arr[i];
            sum += arr[i];
        }

        sum = sum / n;

        for (int i = 0; i<n; i++){
            if(sum > arr[i]){
                Positive += (int)((sum - arr[i]) * 100) / 100.0;
            } else {
                Negative += (int)((arr[i] - sum) * 100) / 100.0;
            }
        }

        fout << "$" << fixed << setprecision(2) << max(Positive, Negative) << endl;

    }

    fin.close();
    fout.close(); 

    return 0;
}
