#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <cmath>

using namespace std;

// Function to split a string by spaces
vector<string> split(const string &s)
{
  vector<string> result;
  stringstream ss(s);
  string item;
  while (getline(ss, item, ' '))
  {
    if (!item.empty())
    {
      result.push_back(item);
    }
  }
  return result;
}

unordered_map<string, string> parent;
unordered_map<string, vector<string>> children;

// Function to find the least common ancestor
string findLCA(const string &a, const string &b)
{
  unordered_map<string, int> ancestors;
  string cur = a;
  int depth = 0;
  while (cur != "")
  {
    ancestors[cur] = depth++;
    cur = parent[cur];
  }
  cur = b;
  depth = 0;
  while (cur != "")
  {
    if (ancestors.count(cur))
      return cur;
    cur = parent[cur];
  }
  return "";
}

// Function to calculate the depth of a node
int getDepth(const string &node)
{
  int depth = 0;
  string cur = node;
  while (cur != "")
  {
    cur = parent[cur];
    depth++;
  }
  return depth;
}

// Function to determine the relationship between two nodes
string determineRelationship(const string &p, const string &q)
{
  if (p == q)
    return "no relation";
  if (parent[p] == q)
    return "child";
  if (parent[q] == p)
    return "parent";

  string cur = p;
  int descendent_count = 0;
  while (parent[cur] != "")
  {
    cur = parent[cur];
    descendent_count++;
    if (cur == q)
    {
      if (descendent_count == 1)
        return "grand child";
      string result = "";
      for (int i = 1; i < descendent_count - 1; ++i)
      {
        result += "great ";
      }
      result += "grand child";
      return result;
    }
  }

  cur = q;
  descendent_count = 0;
  while (parent[cur] != "")
  {
    cur = parent[cur];
    descendent_count++;
    if (cur == p)
    {
      if (descendent_count == 1)
        return "grand parent";
      string result = "";
      for (int i = 1; i < descendent_count - 1; ++i)
      {
        result += "great ";
      }
      result += "grand parent";
      return result;
    }
  }

  string lca = findLCA(p, q);
  if (lca == "")
    return "no relation";

  int depth_p = getDepth(p) - getDepth(lca);
  int depth_q = getDepth(q) - getDepth(lca);
  if (depth_p == 1 && depth_q == 1)
    return "sibling";

  int k = min(depth_p, depth_q) - 1;
  int m = abs(depth_p - depth_q);
  if (k == 0 && m == 0)
    return "sibling";
  if (m == 0)
    return to_string(k) + " cousin";
  return to_string(k) + " cousin removed " + to_string(m);
}

int main()
{
  ifstream fin("tree.inp");
  ofstream fout("tree.out");
  string line;

  // Read child-parent pairs
  while (getline(fin, line))
  {
    vector<string> parts = split(line);
    if (parts[0] == "no.child" && parts[1] == "no.parent")
      break;
    string child = parts[0];
    string par = parts[1];
    parent[child] = par;
    children[par].push_back(child);
  }

  // Read and process query pairs
  while (getline(fin, line))
  {
    vector<string> parts = split(line);
    string p = parts[0];
    string q = parts[1];
    fout << determineRelationship(p, q) << endl;
  }

  fin.close();
  fout.close();
  return 0;
}
