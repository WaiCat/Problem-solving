#include <iostream>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

int nextIndex;
char parenthesisString[2001];
int bracketPositions[1001];
vector<char> outputTree;

void generateTree(int start, int end)
{
    if (start == end)
        return;

    int mid;
    for (mid = start; mid < end; ++mid)
    {
        if (bracketPositions[mid] == nextIndex)
            break;
    }

    nextIndex++;
    outputTree.push_back('(');
    generateTree(start, mid);
    outputTree.push_back(')');
    generateTree(mid + 1, end);
}

int main()
{
    ifstream fin("transform.inp");
    ofstream fout("transform.out");

    int T;
    fin >> T;

    while (T--)
    {
        int n, k;
        fin >> n >> k;

        fout << n << ' ';
        if (k)
        {
            fin >> parenthesisString;

            stack<int> stackIndices;
            for (int i = 0, index = 1; i < 2 * n; ++i)
            {
                if (parenthesisString[i] == '(')
                    stackIndices.push(index++);
                else if (parenthesisString[i] == ')')
                {
                    fout << stackIndices.top() << ' ';
                    stackIndices.pop();
                }
            }
        }
        else
        {
            for (int i = 0; i < n; ++i)
                fin >> bracketPositions[i];

            nextIndex = 1;
            outputTree.clear();
            generateTree(0, n);

            for (char bracket : outputTree)
                fout << bracket;
        }
        fout << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}
