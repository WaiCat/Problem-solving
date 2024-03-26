#include <fstream>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct grid
{
  int state;
  deque<int> d;

  grid() : state(0){}
};

int main() {
  ifstream fin;
  ofstream fout;
  fin.open("0.inp");
  fout.open("0.txt");

  int t;
  fin >> t;

  for (int j = 0; j < t; j++) {
    int x, y, a, b, g;
    fin >> x >> y >> a >> b >> g;

    vector<vector<grid>> vector2D(x+1, vector<grid>(y+1));

    for (int i = 0; i <= x; i++)
    {
      for (int q = 0; q <= y; q++)
      {
        vector2D[i][q].d = deque<int>(g+1, 0);
      }
    }

    for (int i = 0; i < a; i++)
    {
      int q, w;
      fin>>q>>w;
      vector2D[q][w].state = 1;
    }
    for (int i = 0; i < b; i++)
    {
      int q, w;
      fin>>q>>w;
      vector2D[q][w].state = 2;
    }
    
    vector2D[0][0].d.push_front(1);
    vector2D[0][0].d.pop_back();
    for (int i = 1; i <= x; i++)
  {
        
        if(vector2D[i][0].state==1){
          vector2D[i][0].d = vector2D[i-1][0].d;
          int n = vector2D[i][0].d.back();
        vector2D[i][0].d.pop_back();
        vector2D[i][0].d.back() += n;
        vector2D[i][0].d.push_front(0);
        }else if(vector2D[i][0].state==0){
          vector2D[i][0].d = vector2D[i-1][0].d;
        }
        
  }

    for (int i = 1; i <= y; i++)
  {
        if(vector2D[0][i].state==1){
          vector2D[0][i].d = vector2D[0][i-1].d;
          int n = vector2D[0][i].d.back();
          cout << "Deque elements: ";
    for (int u = 0; u < vector2D[0][i].d.size(); ++u) {
        cout << vector2D[0][i].d[u] << " ";
    }
    cout << endl;
        vector2D[0][i].d.pop_back();
        vector2D[0][i].d.back() += n;
        if(vector2D[0][i].d.empty()){
            cout << endl;
        }
        vector2D[0][i].d.push_front(0);
        }else if(vector2D[0][i].state==0){
          vector2D[0][i].d = vector2D[0][i-1].d;
        }
        
  }
  

  for (int i = 1; i < x; i++)
  {
    for (int k = 1; k < y; k++)
    {
      if(vector2D[i][k].state==0){
          deque<int> d, q, e;
          q = vector2D[x - 1][y].d;
          e = vector2D[x][y - 1].d;
          for (int l = 0; l < g+1; l++)
          {
              d.push_back(q[i] + e[i]);
          }
          vector2D[i][k].d = d;
      }else if(vector2D[i][k].state == 1){
        deque<int> d, q, e;
          q = vector2D[x - 1][y].d;
          e = vector2D[x][y - 1].d;
          for (int l = 0; l < g+1; l++)
          {
              d.push_back(q[i] + e[i]);
          }
          int n = d.back();
          d.pop_back();
          d.back() += n;
          d.push_front(0);
          vector2D[i][k].d = d;
      }
    }
    
  }

  fout << vector2D[x][y].d.back() << endl;
  }

    

  fin.close();
  fout.close();

  return 0;
}
