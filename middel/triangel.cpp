#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Point {
 public:
  int x, y;
};

double distance(Point p1, Point p2) {
    return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

int main() {
    ifstream fin("triangel.inp");
  ofstream fout("triangel.out");

    int n;
  fin >> n;

    for (int i = 0; i < n; i++)
    {
        Point a, b, c;
        fin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        double d1, d2, d3;
        d1=distance(a, b);
        d2 = distance(b, c);
        d3 = distance(c, a);
        double sum = d1 + d2 + d3;

        double m = max(max(d1, d2), d3);
        sum -= m;

        if(sum > m){
            fout << 0;
        }else if(sum < m){
            fout << 2;
        }else{
            fout << 1;
        }
        fout << endl;
    }
 
return 0;
}