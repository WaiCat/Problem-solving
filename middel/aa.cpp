#define ll long long int
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct pa {
	ll x, y, p, q;

	bool operator<(struct pa& t) {
		if (q * t.p == p * t.q) {
			if (x == t.x) {
				return y < t.y;
			}
			else if (y == t.y) {
				return x < t.x;
			}
			if (p * q > 0 && t.q * t.p > 0) return y < t.y;
			return y > t.y;
		}
		else return q * t.p < p* t.q;
	}
};

int ccw(pa a, pa b, pa c) {
	ll temp = a.x * b.y + a.y * c.x + b.x * c.y - a.y * b.x - a.x * c.y - b.y * c.x;
	if (temp < 0) return -1;
	else return 1;
}

vector<struct pa> V;
int N;
vector<struct pa> ans;

int main()
{
  ifstream fin("1.inp");
  ofstream fout("1.txt");

  int t;
  fin >> t;
  for (size_t j = 0; j < t; j++)
  {
    for (int i = 0; i < 4; i++) {
		ll x, y;
		fin >> x >> y;
		V.push_back({ x,y,0,0 });
		if (V[i].x < V[0].x) {
			pa temp = V[0];
			V[0] = V[i];
			V[i] = temp;
		}
		if (V[i].x == V[0].x && V[i].y < V[0].y) {
			ll temp = V[0].y;
			V[0].y = V[i].y;
			V[i].y = temp;
		}
	}

	for (int i = 1; i < V.size(); i++) {
		V[i].p = V[0].x - V[i].x;
		V[i].q = V[0].y - V[i].y;
	}
	
	sort(V.begin() + 1, V.end());

	ans.push_back(V[0]);
	ans.push_back(V[1]);
	for (int i = 2; i < N; i++) {
		while (ans.size() >= 2 && ccw(ans[ans.size() - 1], ans[ans.size() - 2], V[i]) > 0) {
			ans.pop_back();
		}
		ans.push_back(V[i]);
	}
  if(ans.size()<4){
	fout << 2 << "\n";
  }else{
	fout << 3 << "\n";

  }
  }
  
	
	
	return 0;
}