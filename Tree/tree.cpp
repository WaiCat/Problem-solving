#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, string> parent;
unordered_map<string, vector<string>> children;
unordered_map<string, int> depth;

void computeDepth(const string& node, int d) {
  depth[node] = d;
  for (const string& child : children[node]) {
    computeDepth(child, d + 1);
  }
}

string findLCA(const string& p, const string& q) {
  unordered_map<string, bool> visited;
  string temp = p;
  while (!temp.empty()) {
    visited[temp] = true;
    temp = parent[temp];
  }
  temp = q;
  while (!temp.empty()) {
    if (visited[temp]) return temp;
    temp = parent[temp];
  }
  return "";
}

string relationship(const string& p, const string& q) {
  if (parent[q] == p) return "parent";
  if (parent[p] == q) return "child";

  int pDepth = depth[p];
  int qDepth = depth[q];

  string lca = findLCA(p, q);
  if (lca.empty()) return "no relation";

  int lcaDepth = depth[lca];
  int pDiff = pDepth - lcaDepth;
  int qDiff = qDepth - lcaDepth;

  if (lca == p || lca == q) {
    if (pDiff == 1) return "grand child";
    if (qDiff == 1) return "grand parent";
    string relation = "";
    if (lca == p) {
      for (int i = 1; i < pDiff; ++i) relation += "great ";
      relation += "grand child";
    } else {
      for (int i = 1; i < qDiff; ++i) relation += "great ";
      relation += "grand parent";
    }
    return relation;
  }

  int cousinLevel = min(pDiff, qDiff) - 1;
  int removed = abs(pDiff - qDiff);

  if (cousinLevel == 0 && removed == 0) return "sibling";

  string result = to_string(cousinLevel) + " cousin";
  if (removed > 0) result += " removed " + to_string(removed);
  return result;
}

int main() {
  ifstream infile("1.inp");
  ofstream outfile("1.txt");

  string line;
  vector<pair<string, string>> queries;

  while (getline(infile, line)) {
    stringstream ss(line);
    string child, par;
    ss >> child >> par;
    if (child == "no.child" && par == "no.parent") break;
    parent[child] = par;
    children[par].push_back(child);
  }

  // Compute depth of each node
  for (const auto& p : parent) {
    if (depth.find(p.first) == depth.end()) {
      computeDepth(p.first, 0);
    }
  }

  while (getline(infile, line)) {
    stringstream ss(line);
    string p, q;
    ss >> p >> q;
    queries.push_back({p, q});
  }

  for (const auto& query : queries) {
    outfile << relationship(query.first, query.second) << endl;
  }

  infile.close();
  outfile.close();

  return 0;
}
