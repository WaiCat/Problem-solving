#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Prediction
{
    int bulb1, bulb2, bulb3;
    char color1, color2, color3;
};

class TwoSat
{
public:
    TwoSat(int n) : n(n), adj(2 * n), radj(2 * n), assignment(n), visited(2 * n, false), comp(2 * n, -1) {}

    void add_clause(int u, bool u_neg, int v, bool v_neg)
    {
        int not_u = u + (u_neg ? n : 0);
        int not_v = v + (v_neg ? n : 0);
        u = u + (u_neg ? 0 : n);
        v = v + (v_neg ? 0 : n);
        adj[not_u].push_back(v);
        adj[not_v].push_back(u);
        radj[v].push_back(not_u);
        radj[u].push_back(not_v);
    }

    bool solve()
    {
        for (int i = 0; i < 2 * n; ++i)
        {
            if (!visited[i])
                dfs1(i);
        }
        fill(visited.begin(), visited.end(), false);
        int id = 0;
        while (!order.empty())
        {
            int v = order.top();
            order.pop();
            if (!visited[v])
                dfs2(v, id++);
        }
        for (int i = 0; i < n; ++i)
        {
            if (comp[i] == comp[i + n])
                return false;
            assignment[i] = comp[i] > comp[i + n];
        }
        return true;
    }

    vector<bool> get_assignment()
    {
        return assignment;
    }

private:
    int n;
    vector<vector<int>> adj, radj;
    vector<int> comp;
    vector<bool> visited;
    stack<int> order;
    vector<bool> assignment;

    void dfs1(int v)
    {
        visited[v] = true;
        for (int u : adj[v])
        {
            if (!visited[u])
                dfs1(u);
        }
        order.push(v);
    }

    void dfs2(int v, int id)
    {
        visited[v] = true;
        comp[v] = id;
        for (int u : radj[v])
        {
            if (!visited[u])
                dfs2(u, id);
        }
    }
};

int main()
{
    ifstream inFile("show.inp");
    ofstream outFile("show.out");

    int T;
    inFile >> T;

    while (T--)
    {
        int K, N;
        inFile >> K >> N;

        vector<Prediction> predictions(N);
        for (int i = 0; i < N; ++i)
        {
            inFile >> predictions[i].bulb1 >> predictions[i].color1 >> predictions[i].bulb2 >> predictions[i].color2 >> predictions[i].bulb3 >> predictions[i].color3;
        }

        TwoSat solver(K);

        for (const auto &prediction : predictions)
        {
            int b1 = prediction.bulb1 - 1;
            int b2 = prediction.bulb2 - 1;
            int b3 = prediction.bulb3 - 1;
            bool c1 = (prediction.color1 == 'R');
            bool c2 = (prediction.color2 == 'R');
            bool c3 = (prediction.color3 == 'R');

            solver.add_clause(b1, !c1, b2, !c2);
            solver.add_clause(b1, !c1, b3, !c3);
            solver.add_clause(b2, !c2, b3, !c3);
        }

        bool result = solver.solve();
        outFile << (result ? 1 : -1) << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}
